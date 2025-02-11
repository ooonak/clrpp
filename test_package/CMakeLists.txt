cmake_minimum_required(VERSION 3.30.3)
project(PackageTest CXX)

find_package(clrpp CONFIG REQUIRED)

find_package(spdlog CONFIG REQUIRED)
find_package(CapnProto CONFIG REQUIRED)


add_executable(example example.cpp)
target_link_libraries(example clrpp::clrpp)
