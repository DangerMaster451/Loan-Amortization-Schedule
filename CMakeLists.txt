cmake_minimum_required(VERSION 3.20)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(MyApp
    src/source.cpp
    src/loan.cpp
)