cmake_minimum_required(VERSION 3.16)
project(CrystalCaverns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CrystalCaverns
    src/SpielStart.cpp
    src/Spiel.cpp
    src/Tastatur.cpp
    src/Bilder.cpp
    src/Feld.cpp
    src/LevelKarte.cpp
    src/Figur.cpp
    src/Spieler.cpp
    src/Gegner.cpp
    src/Stein.cpp
)

target_include_directories(CrystalCaverns PRIVATE include)

find_package(SDL2 QUIET)
if(SDL2_FOUND)
    target_link_libraries(CrystalCaverns PRIVATE SDL2::SDL2)
else()
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2_PKG QUIET sdl2)
    endif()

    if(SDL2_PKG_FOUND)
        target_include_directories(CrystalCaverns PRIVATE ${SDL2_PKG_INCLUDE_DIRS})
        target_link_directories(CrystalCaverns PRIVATE ${SDL2_PKG_LIBRARY_DIRS})
        target_link_libraries(CrystalCaverns PRIVATE ${SDL2_PKG_LIBRARIES})
    else()
        find_program(SDL2_CONFIG sdl2-config)
        if(SDL2_CONFIG)
            execute_process(COMMAND ${SDL2_CONFIG} --cflags OUTPUT_VARIABLE SDL2_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
            execute_process(COMMAND ${SDL2_CONFIG} --libs OUTPUT_VARIABLE SDL2_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
            separate_arguments(SDL2_CFLAGS)
            separate_arguments(SDL2_LIBS)
            target_compile_options(CrystalCaverns PRIVATE ${SDL2_CFLAGS})
            target_link_libraries(CrystalCaverns PRIVATE ${SDL2_LIBS})
        else()
            message(FATAL_ERROR "SDL2 was not found. Install it first, e.g. macOS: brew install sdl2, Ubuntu/Kali: sudo apt install libsdl2-dev")
        endif()
    endif()
endif()

if(APPLE)
    target_compile_definitions(CrystalCaverns PRIVATE SDL_MAIN_HANDLED)
endif()
