cmake_minimum_required(VERSION 3.23)

project(game-project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Main)
add_library(Game)
add_library(Farm)
add_library(Soldier)
add_library(HealthBar)
add_library(IDamageable INTERFACE)
add_library(Menu)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

target_link_libraries(Main
    PRIVATE
        Game Farm Soldier HealthBar IDamageable Menu sfml-graphics sfml-window sfml-system)

target_link_libraries(Farm PUBLIC IDamageable)
target_link_libraries(Soldier PUBLIC IDamageable)
target_link_libraries(Game PUBLIC Menu)

target_sources(Main
        PRIVATE
            src/main.cpp
)

target_sources(Game
        PRIVATE
            src/Game.cpp

        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS src
            FILES src/Game.hpp
)

target_sources(Farm
        PRIVATE
            src/Farm.cpp

        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS src
            FILES src/Farm.hpp
)

target_sources(Soldier
        PRIVATE
            src/Soldier.cpp

        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS src
            FILES src/Soldier.hpp
)

target_sources(HealthBar
        PRIVATE
            src/HealthBar.cpp

        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS src
            FILES src/HealthBar.hpp
)

target_sources(IDamageable
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS src
        FILES src/IDamageable.hpp)

target_sources(Menu
    PRIVATE
        src/Menu.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS src
        FILES src/Menu.hpp)