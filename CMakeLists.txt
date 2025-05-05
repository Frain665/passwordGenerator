cmake_minimum_required(VERSION 3.16)

project(passwordGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML)
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

file(GLOB SOURCES src/*.cpp )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)

if(WIN32)
    file(GLOB SFML_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/bin/*.dll")
    file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()