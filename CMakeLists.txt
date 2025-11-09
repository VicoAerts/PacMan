cmake_minimum_required(VERSION 3.22.1)
project(PacMan)

set(CMAKE_CXX_STANDARD 20)


add_executable(PacMan main.cpp
        src/model/World.cpp
        src/model/World.h
        src/view/Game.cpp
        src/view/Game.h
        src/states/LevelState.cpp
        src/states/LevelState.h
        src/states/PausedState.cpp
        src/states/PausedState.h
        src/states/VictoryState.cpp
        src/states/VictoryState.h
        src/states/GameOverState.cpp
        src/states/GameOverState.h
        src/states/MenuState.cpp
        src/states/MenuState.h
        src/states/State.cpp
        src/states/State.h
        src/events/Event.cpp
        src/events/Event.h
        src/model/Clock.cpp
        src/model/Clock.h
)

TARGET_LINK_LIBRARIES(PacMan sfml-system sfml-graphics sfml-window)