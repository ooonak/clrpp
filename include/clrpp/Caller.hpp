#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include "clrpp/MethodRegistry.hpp"

namespace clr {

  class Caller {
    public:
      explicit Caller(const std::string& socketPath);

      ~Caller();

      template <typename Func>
      bool bind(const std::string& name, Func func) {
        return true;
      }

      /**
       * Listen for incomming method calls from server, blocks.
       */
      void run();

      void stop();

    private:
      int sockFd;
      using RegistryT = std::unordered_map<std::string, std::function<void(capnp::List<capnp::AnyPointer>::Reader)>>;
      RegistryT methodRegistry;

  };

} // namespace clr
