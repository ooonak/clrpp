#pragma once

#include <string_view>

const std::string_view SOCKET_PATH = "/tmp/rpc_test_server.sock";

namespace clr {

void test_server();

} // namespace clr
