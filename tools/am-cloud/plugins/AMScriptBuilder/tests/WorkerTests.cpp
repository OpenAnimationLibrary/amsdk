#include "../Worker.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
void Check(bool condition, const char* description) { if (!condition) throw std::runtime_error(description); }
int wmain(int argc, wchar_t** argv) {
    try {
        Check(argc == 3, "Expected Python and scratch path arguments");
        const std::wstring python = argv[1];
        const auto root = fs::absolute(argv[2]);
        const auto folder = root / L"worker path space \u65e5 & test";
        fs::create_directories(folder);
        const auto source = folder / L"input \u00e9.py";
        DWORD before = 0, after = 0;
        Check(GetProcessHandleCount(GetCurrentProcess(), &before) != 0, "Cannot count initial handles");
        auto run = [&](const char* name, const std::string& code, bool success, DWORD deadline = 5000) {
            std::cout << "CASE: " << name << std::endl;
            std::ofstream(source, std::ios::binary) << code;
            amscript::Worker worker;
            bool good = false;
            try {
                worker.start(python, {L"-I", L"-S", L"-B", L"-X", L"utf8", source.wstring()}, folder.wstring(), deadline);
                while (!worker.poll()) Sleep(10);
                good = true;
            } catch (const std::exception& error) {
                std::cout << "Worker result: " << error.what() << "\n"
                          << worker.errors.substr(0, 2000) << std::endl;
                worker.stop();
            }
            Check(good == success, name);
            std::cout << "CASE PASS: " << name << "; stdout bytes=" << worker.output.size() << std::endl;
            return worker.output;
        };
        Check(run("initial stdout", "print('hello')", true).find("hello") != std::string::npos, "Missing hello output");
        DWORD warmed = 0;
        Check(GetProcessHandleCount(GetCurrentProcess(), &warmed) != 0, "Cannot count warm handles");
        std::cout << "Handles at entry=" << before << "; after first process=" << warmed << std::endl;
        // Run #3 observed 46 handles at entry, 59 after first process, then 59/59
        // across both batches. Measure repeat growth, not the cold-start delta.
        for (unsigned pass = 0; pass < 2; ++pass) {
            Check(GetProcessHandleCount(GetCurrentProcess(), &before) != 0, "Cannot count batch handles");
            Check(run("Unicode arguments", "import sys;print(sys.argv[0])", true).find("input") != std::string::npos, "Missing Unicode script path");
            run("script exception", "raise RuntimeError('expected failure')", false);
            run("stdout limit", "import sys;sys.stdout.write('x'*300000)", false);
            run("stderr limit", "import sys;sys.stderr.write('x'*20000)", false);
            run("wall timeout", "while True: pass", false, 300);
            run("memory limit", "value=bytearray(1024*1024*1024)", false);
            run("child process limit", "import subprocess,sys;subprocess.run([sys.executable,'-c','pass'],check=True)", false);
            run("recovery", "print('still healthy')", true);
            {
                std::cout << "CASE: immediate cancellation" << std::endl;
                amscript::Worker worker;
                std::ofstream(source) << "while True: pass";
                worker.start(python, {L"-I", L"-S", source.wstring()}, folder.wstring());
                worker.stop();
            }
            Check(GetProcessHandleCount(GetCurrentProcess(), &after) != 0, "Cannot count final handles");
            std::cout << "Batch " << pass << ": handles before=" << before << "; after=" << after << std::endl;
            if (pass) Check(after <= before, "Unexpected handle growth across the repeated worker batch");
        }
        fs::remove(source); fs::remove(folder);
        std::cout << "PASS: Unicode/space paths, exit failure, stdout/stderr flood, timeout, memory/child-process limits, cancellation and repeated-batch handle cleanup\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
