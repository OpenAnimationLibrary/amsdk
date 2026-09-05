#include "../Worker.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
void Check(bool condition) { if (!condition) throw std::runtime_error("Worker test assertion failed"); }
int wmain(int argc, wchar_t** argv) {
    try {
        Check(argc == 3);
        const std::wstring python = argv[1];
        const auto root = fs::absolute(argv[2]);
        const auto folder = root / L"worker path space \u65e5 & test";
        fs::create_directories(folder);
        const auto source = folder / L"input \u00e9.py";
        DWORD before = 0, after = 0;
        Check(GetProcessHandleCount(GetCurrentProcess(), &before) != 0);
        auto run = [&](const std::string& code, bool success, DWORD deadline = 5000) {
            std::ofstream(source, std::ios::binary) << code;
            amscript::Worker worker;
            bool good = false;
            try {
                worker.start(python, {L"-I", L"-S", L"-B", L"-X", L"utf8", source.wstring()}, folder.wstring(), deadline);
                while (!worker.poll()) Sleep(10);
                good = true;
            } catch (const std::exception&) { worker.stop(); }
            Check(good == success);
            return worker.output;
        };
        Check(run("print('hello')", true).find("hello") != std::string::npos);
        Check(run("import sys;print(sys.argv[0])", true).find("input") != std::string::npos);
        run("raise RuntimeError('expected failure')", false);
        run("import sys;sys.stdout.write('x'*300000)", false);
        run("import sys;sys.stderr.write('x'*20000)", false);
        run("while True: pass", false, 300);
        run("import subprocess,sys;subprocess.run([sys.executable,'-c','pass'],check=True)", false);
        run("print('still healthy')", true);
        {
            amscript::Worker worker;
            std::ofstream(source) << "while True: pass";
            worker.start(python, {L"-I", L"-S", source.wstring()}, folder.wstring());
            worker.stop(); // cancellation must not wait for the script to finish itself
        }
        Check(GetProcessHandleCount(GetCurrentProcess(), &after) != 0);
        Check(after <= before + 1);
        fs::remove(source); fs::remove(folder);
        std::cout << "PASS: Unicode/space paths, exit failure, stdout/stderr flood, timeout, child-process limit, cancellation and handle cleanup\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
