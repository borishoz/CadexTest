cmake_minimum_required(VERSION 3.5)

project(CadexTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER_ID: g++)
set(CMAKE_C_COMPILER_VERSION: 10.0.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

set(SOURCE main.cpp cadextest.cpp curves.cpp)

add_executable(CadexTest ${SOURCE})
