cmake_minimum_required(VERSION 3.30.3)
project(PackageTest CXX)

find_package(clrpp CONFIG REQUIRED)

add_executable(example example.cpp)

target_link_libraries(example clrpp::clrpp)
