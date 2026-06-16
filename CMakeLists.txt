cmake_minimum_required(VERSION 3.10)

project(AsciiRenderer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAEK_CXX_STANDARD_REQUIRED ON)

add_executable(ascii_r main2.cpp domain.cpp renderer.cpp Camera.cpp)
