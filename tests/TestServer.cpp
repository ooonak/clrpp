#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <thread>
#include "spdlog/spdlog.h"
#include "capnp/message.h"
#include "capnp/serialize.h"
#include "ClrMsgs.capnp.h"

namespace clr {

void test_server() {
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH.c_str());
    unlink(SOCKET_PATH.c_str());

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 1);
    int client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Read method registration from client
    ::capnp::MallocMessageBuilder msg;
    auto reader = readMessageFromFd(client_fd, capnp::ReaderOptions());
    auto method_register = reader.getRoot<MethodRegister>();

    std::string method_name = method_register.getMethodName();
    spdlog::info("✅ Method registered: {}", method_name);

    // Send a test method call
    ::capnp::MallocMessageBuilder request;
    auto method_call = request.initRoot<MethodCall>();
    method_call.setMethodName("add");
    auto args = method_call.initArgs(2);
    args.set(0, "5");
    args.set(1, "3");

    writeMessageToFd(client_fd, request);

    // Read client response
    auto response_reader = readMessageFromFd(client_fd, capnp::ReaderOptions());
    auto method_return = response_reader.getRoot<MethodReturn>();

    std::string result = method_return.getResult();
    spdlog::info("✅ Client returned result: {}", result);

    close(client_fd);
    close(server_fd);
}

}