cmake_minimum_required(VERSION 3.30.3)

project(clrppTests LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  clrppTests.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  clrpp::clrpp
  spdlog::spdlog
  capnproto::capnproto
  GTest::gtest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

