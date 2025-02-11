cmake_minimum_required(VERSION 3.30.3)
project(clrpp CXX)

# Generate C++ code from Cap'n Proto schema files
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS rpc.capnp)

add_library(clrpp
  ../include/clrpp/clrpp.hpp
  ${CAPNP_SRCS}
  ${CAPNP_HDRS}
  clrpp.cpp)

if(STRICT_WARNINGS)
  set_warnings(${PROJECT_NAME})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(clrpp PRIVATE spdlog::spdlog)
target_link_libraries(clrpp PRIVATE capnproto::capnproto)

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
