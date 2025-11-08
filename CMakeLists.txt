cmake_minimum_required(VERSION 4.0)
project(PacMan)

set(CMAKE_CXX_STANDARD 20)


add_executable(PacMan main.cpp)

TARGET_LINK_LIBRARIES(PacMan sfml-system sfml-graphics sfml-window)