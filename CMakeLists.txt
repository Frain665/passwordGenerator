cmake_minimum_required(VERSION 3.10)

project(passwordGenerator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(passwordGenerator 
src/main.cpp
src/Engine.cpp
src/ApplicationMenu.cpp
)