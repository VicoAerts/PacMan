cmake_minimum_required(VERSION 3.22.1)
project(PacMan)

set(CMAKE_CXX_STANDARD 17)
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

SET(LOGIC_SRC
        src/model/World.cpp
        src/model/World.h
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
        src/model/Clock.cpp
        src/model/Clock.h

)
ADD_LIBRARY(PacMan STATIC ${LOGIC_SRC})


SET(VIEW_SRC
        src/view/Game.cpp
        src/view/Game.h
        src/events/Event.cpp
        src/events/Event.h

)

ADD_EXECUTABLE(Pacman main.cpp ${VIEW_SRC})


TARGET_LINK_LIBRARIES(Pacman PacMan sfml-system sfml-graphics sfml-window)