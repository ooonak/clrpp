cmake_minimum_required(VERSION 3.30.3)

project(
  clrpp
  VERSION 0.0.1
  DESCRIPTION "Caller C++ client library"
  LANGUAGES CXX)

option(TESTS "Build tests" ON)
option(STATIC_ANALYSIS "Run clang-tidy and CppCheck status analysis tools" OFF)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_VERBOSE_MAKEFILE ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
  include(static_analysis)

  if(STATIC_ANALYSIS)
    enable_clang_tidy()
    enable_cppcheck()
  endif()

  include(GNUInstallDirs)
  include(CTest)
endif()

find_package(spdlog CONFIG REQUIRED)
find_package(CapnProto CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(example)

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
  AND TESTS)
  find_package(GTest REQUIRED CONFIG)
  add_subdirectory(tests)
endif()

