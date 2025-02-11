cmake_minimum_required(VERSION 3.30.3)
project(clrpp CXX)

add_library(clrpp
  ../include/clrpp/clrpp.hpp
  clrpp.cpp)

if(STRICT_WARNINGS)
  set_warnings(${PROJECT_NAME})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(clrpp PRIVATE spdlog::spdlog)
target_link_libraries(clrpp PRIVATE capnproto::capnproto)

# All users of this library will need at least C++23
#target_compile_features(clrpp PUBLIC cxx_std_23)

add_library(clrpp::clrpp ALIAS clrpp)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/clrpp
        DESTINATION include
        COMPONENT Devel
)
