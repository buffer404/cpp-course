cmake_minimum_required(VERSION 3.5)
project (lab2)

add_executable(${PROJECT_NAME} main.cpp
                               src/CustomClass.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/)
