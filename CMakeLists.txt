cmake_minimum_required(VERSION 3.5)

project(CadexTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE main.cpp cadextest.cpp)

add_executable(CadexTest ${SOURCE})
