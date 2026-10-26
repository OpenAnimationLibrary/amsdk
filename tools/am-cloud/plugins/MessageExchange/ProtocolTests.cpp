#include "ExchangeProtocol.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {
void require(bool condition) {
    if (!condition) throw std::runtime_error("Message protocol check failed.");
}
}

int main() {
    AMMessageRequest request;
    AMMessageReply reply;
    int context = 7;
    request.context = &context;
    std::snprintf(request.message, sizeof(request.message), "Hello from Plugin A.");
    int calls = 0;
    auto completed = [&](const AMMessageRequest &input) {
        require(input.context == &context);
        require(std::strcmp(input.message, "Hello from Plugin A.") == 0);
        ++calls;
        return true;
    };
    require(ReceiveAMMessage(&request, &reply, "Plugin B", completed) == AM_MESSAGE_OK);
    require(calls == 1 && context == 7);
    require(std::strcmp(reply.message, "Plugin B received your message and completed its task.") == 0);
    auto cancelled = [&](const AMMessageRequest &) { ++calls; return false; };
    require(ReceiveAMMessage(&request, &reply, "Plugin B", cancelled) == AM_MESSAGE_CANCELLED);
    require(std::strcmp(reply.message, "Plugin B cancelled its task.") == 0 && calls == 2);
    const auto rejected = [&]() {
        require(ReceiveAMMessage(&request, &reply, "Plugin B", completed) == AM_MESSAGE_INVALID);
        require(calls == 2);
    };
    request.version = 2; rejected(); request.version = AM_MESSAGE_VERSION;
    request.size = 0; rejected(); request.size = sizeof(request);
    reply.version = 2; rejected(); reply.version = AM_MESSAGE_VERSION;
    reply.size = 0; rejected(); reply.size = sizeof(reply);
    request.context = nullptr; rejected(); request.context = &context;
    request.message[0] = '\0'; rejected();
    std::memset(request.message, 'x', sizeof(request.message)); rejected();
    require(ReceiveAMMessage(nullptr, &reply, "Plugin B", completed) == AM_MESSAGE_INVALID);
    require(ReceiveAMMessage(&request, nullptr, "Plugin B", completed) == AM_MESSAGE_INVALID);
    require(ReceiveAMMessage(&request, &reply, nullptr, completed) == AM_MESSAGE_INVALID);
    std::cout << "Message protocol: completion, cancellation, context and invalid-input checks passed.\n";
    return EXIT_SUCCESS;
}
