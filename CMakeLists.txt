cmake_minimum_required(VERSION 3.10)

project(passwordGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-master)

add_executable(passwordGenerator 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/InterfaceElements.cpp
)

target_include_directories(passwordGenerator PRIVATE 
    include
)

target_link_libraries(passwordGenerator PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)