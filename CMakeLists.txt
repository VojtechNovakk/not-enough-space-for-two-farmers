cmake_minimum_required(VERSION 3.16)

project(farmers LANGUAGES CXX)

# Force out-of-source builds: everything CMake generates must live in build/
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not allowed. Run:\n"
        "  cmake -B build\n"
        "  cmake --build build")
endif()

# Put the final binary in build/ itself, not build/<config>/ on multi-config generators
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 2.5 as installed by the system package manager (libsfml-dev).
# "graphics" pulls in window + system automatically.
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(farmers
    src/main.cpp
    src/Game.cpp
    src/Farm.cpp
    src/Soldier.cpp
    src/HealthBar.cpp
)

# Lets you write #include "Game.hpp" instead of "../src/Game.hpp"
target_include_directories(farmers PRIVATE src)

# Warnings. -Wconversion catches the silent numeric conversions that bit us
# before (bool passed where an int was expected, double narrowed to float).
target_compile_options(farmers PRIVATE
    -Wall
    -Wextra
    -Wconversion
)

target_link_libraries(farmers PRIVATE sfml-graphics sfml-audio)
