#include "../StudioPlan.h"
#include "../ReceiverSafety.h"
#include <algorithm>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
namespace {
void Require(bool value) {
    if(!value) throw std::runtime_error("Receiver safety regression");
}
struct TestReceiver : patchstudio::ReceiverLifetime {
    int* destroyed;
    explicit TestReceiver(int* count) : destroyed(count) {}
    ~TestReceiver() { ++*destroyed; }
};
void SelfTest() {
    int destroyed=0;
    auto* r=new TestReceiver(&destroyed);
    r->windowOwns=true;
    {
        patchstudio::ReceiverCallbackLease<TestReceiver> send(r);
        {
            patchstudio::ReceiverCallbackLease<TestReceiver> nonClientDestroy(r);
            r->detached=true;
        }
        Require(destroyed==0 && r->callbackDepth==1 && r->detached);
        // The send's cleanup/acknowledgement still has a valid receiver here.
    }
    Require(destroyed==1);
    {
        auto creating=std::make_unique<TestReceiver>(&destroyed);
        {
            patchstudio::ReceiverCallbackLease<TestReceiver> init(creating.get());
            creating->detached=true;
        }
        Require(destroyed==1); // failed creation remains command-owned
    }
    Require(destroyed==2);
    auto* live=new TestReceiver(&destroyed); live->windowOwns=true;
    { patchstudio::ReceiverCallbackLease<TestReceiver> timer(live); }
    Require(destroyed==2);
    { patchstudio::ReceiverCallbackLease<TestReceiver> destroy(live); live->detached=true; }
    Require(destroyed==3);
    const std::array<std::size_t,4> expected{0,1,2,3};
    auto order=expected; unsigned accepted=0;
    do { if(patchstudio::SameFaceCycle(order,expected)) ++accepted; }
    while(std::next_permutation(order.begin(),order.end()));
    Require(accepted==8);
    Require(!patchstudio::SameFaceCycle({0,2,1,3},expected));
    std::cout<<"PASS: nested callback destruction, creation failure, idle receiver lifetime and all 24 face permutations\n";
}
}
int main(int argc,char** argv) {
    if(argc!=2) return 2;
    try {
        if(std::string(argv[1])=="--self-test") { SelfTest(); return 0; }
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
