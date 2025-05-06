cmake_minimum_required(VERSION 3.16)
project(passwordGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.6.0/lib/cmake/SFML")
message(STATUS "Looking for SFML in: ${SFML_DIR}")

if(NOT EXISTS "${SFML_DIR}/SFMLConfig.cmake")
    message(FATAL_ERROR "SFMLConfig.cmake not found in ${SFML_DIR}")
endif()

find_package(SFML 2.6.0 EXACT COMPONENTS system window graphics REQUIRED)
message(STATUS "SFML found: ${SFML_VERSION}")

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE "include")

if(TARGET SFML::System)
    message(STATUS "Using SFML imported targets")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
    )
else()
    message(STATUS "Using SFML legacy variables")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SFML_SYSTEM_LIBRARY}
        ${SFML_WINDOW_LIBRARY}
        ${SFML_GRAPHICS_LIBRARY}
    )
endif()

if(WIN32)
    set(SFML_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.6.0/bin")
    if(EXISTS "${SFML_BIN_DIR}")
        file(GLOB SFML_DLLS "${SFML_BIN_DIR}/*.dll")
        if(SFML_DLLS)
            file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
            message(STATUS "Copied SFML DLLs from ${SFML_BIN_DIR}")
        else()
            message(WARNING "No DLLs found in ${SFML_BIN_DIR}")
        endif()
    else()
        message(WARNING "SFML bin directory not found: ${SFML_BIN_DIR}")
    endif()
endif()