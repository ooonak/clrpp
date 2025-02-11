cmake_minimum_required(VERSION 3.30.3)

project(
  clrpp
  VERSION 0.0.1
  DESCRIPTION "Caller C++ client library"
  LANGUAGES CXX)

option(TESTS "Build tests" ON)
option(STATIC_ANALYSIS "Run clang-tidy and CppCheck status analysis tools" OFF)
option(STRICT_WARNINGS "Use strict compiler warnings" ON)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)  
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  set(CMAKE_VERBOSE_MAKEFILE ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-files/cmake")
  include(snippets) 

  if(STATIC_ANALYSIS)
    enable_clang_tidy()
    enable_cppcheck()
  endif()

  include(GNUInstallDirs)
  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
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
  set(CMAKE_PREFIX_PATH "/home/swu/.conan2/p/gtestf46417e2f457c/e")
  find_package(GTest REQUIRED CONFIG)
  add_subdirectory(tests)
endif()

