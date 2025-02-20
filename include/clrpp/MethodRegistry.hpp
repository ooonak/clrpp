#pragma once

#include "capnp/message.h"
#include "capnp/serialize-packed.h"
#include <unordered_map>
#include <string>
#include <tuple>
#include <functional>
#include <iostream>

// 🚀 **Meta-template to extract function signature (return type & arguments)**
template <typename Func>
struct FunctionTraits;

template <typename R, typename... Args>
struct FunctionTraits<R(Args...)> {
    using ReturnType = R;
    using ArgsTuple = std::tuple<Args...>;
    static constexpr size_t ArgCount = sizeof...(Args);
};

template <typename R, typename... Args>
struct FunctionTraits<R(*)(Args...)> : FunctionTraits<R(Args...)> {};

// 🚀 **Serializes arguments into Cap’n Proto**
template <typename... Args>
void serializeArguments(capnp::List<capnp::AnyPointer>::Builder& argsList, Args&&... args) {
    int index = 0;
    (..., (argsList[index++].setAs<std::decay_t<Args>>(std::forward<Args>(args))));
}

// 🚀 **A generic method registry**
class MethodRegistry {
private:
    std::unordered_map<std::string, std::function<void(capnp::List<capnp::AnyPointer>::Reader)>> registry;

public:
    template <typename Func>
    void registerMethod(const std::string& methodName, Func fn) {
        using ArgsTuple = typename FunctionTraits<Func>::ArgsTuple;

        // 🔹 Store method in registry
        registry[methodName] = [fn](capnp::List<capnp::AnyPointer>::Reader args) {
            invokeMethod(fn, args, std::index_sequence_for<typename FunctionTraits<Func>::ArgsTuple>{});
        };

        std::cout << "📌 Registered method: " << methodName << "\n";
    }

    // 🚀 **Invoke registered methods dynamically**
    void invoke(const std::string& methodName, capnp::List<capnp::AnyPointer>::Reader args) {
        if (registry.find(methodName) != registry.end()) {
            registry[methodName](args);
        } else {
            std::cerr << "❌ Method not found: " << methodName << "\n";
        }
    }

private:
    // 🛠 **Helper to invoke a function with unpacked arguments**
    template <typename Func, std::size_t... I>
    static void invokeMethod(Func fn, capnp::List<capnp::AnyPointer>::Reader args, std::index_sequence<I...>) {
        fn(args[I].getAs<typename std::tuple_element<I, typename FunctionTraits<Func>::ArgsTuple>::type>()...);
    }
};

