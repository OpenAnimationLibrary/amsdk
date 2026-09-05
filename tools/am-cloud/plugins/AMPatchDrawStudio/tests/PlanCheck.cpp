#include "../StudioPlan.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
int main(int argc,char** argv) {
    if(argc!=2) return 2;
    try {
        const std::filesystem::path path(argv[1]);
        std::vector<std::filesystem::path> paths;
        if(std::filesystem::is_directory(path)) {
            for(const auto& item:std::filesystem::directory_iterator(path)) if(item.path().extension()==".json") paths.push_back(item.path());
        } else paths.push_back(path);
        std::size_t count=0;
        for(const auto& file:paths) {
            if(std::filesystem::file_size(file)>patchstudio::MaxBytes+1) return 3;
            std::ifstream stream(file,std::ios::binary);
            const std::string data((std::istreambuf_iterator<char>(stream)),{});
            try { const auto plan=patchstudio::Parse(data); if(!plan.faces.empty()) ++count; }
            catch(const std::exception& e) { std::cerr<<file.filename()<<": "<<e.what()<<'\n'; return 1; }
        }
        if(!count) return 4;
        std::cout<<"PASS "<<count<<" native parser fixtures\n";
    } catch(const std::exception& e) { std::cerr<<e.what()<<'\n';return 1; }
}
