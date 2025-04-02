cmake_minimum_required(VERSION 3.26)
project(CS3A_Tetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS3A_Tetris main.cpp
        Block.cpp
        Block.h
        Field.cpp
        Field.h
        Game.cpp
        Game.h
        Settings.h
        SplashScreen.cpp
        SplashScreen.h
        TetrisApp.cpp
        TetrisApp.h

)

target_link_libraries(CS3A_Tetris sfml-graphics sfml-audio)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)