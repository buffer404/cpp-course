cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Debug)
project (lab4)

add_executable(${PROJECT_NAME} main.cpp
                               src/SparceMatrix.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/)
