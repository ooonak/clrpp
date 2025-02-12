cmake_minimum_required(VERSION 3.25)

project(clrppExample LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE
  clrpp::clrpp
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
