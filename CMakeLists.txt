cmake_minimum_required(VERSION 3.22.1)
project(PacMan)

set(CMAKE_CXX_STANDARD 17)
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

SET(LOGIC_SRC
        src/model/World.cpp
        src/model/World.h
        src/util/Clock.cpp
        src/util/Clock.h
        config/config.h
        src/view/Camera.cpp
        src/view/Camera.h
        src/model/Entity.h
        src/model/Subject.cpp
        src/model/Subject.h
        src/model/Observer.cpp
        src/model/Observer.h
        src/model/PacMan.cpp
        src/model/PacMan.h
        src/model/Ghost.cpp
        src/model/Ghost.h
        src/model/Wall.cpp
        src/model/Wall.h
        src/model/Collectable.cpp
        src/model/Collectable.h
        src/util/Random.cpp
        src/util/Random.h
        src/model/AbstractFactory.cpp
        src/model/AbstractFactory.h
        src/model/GridMap.cpp
        src/model/GridMap.h
        src/util/Vec2D.h

)
ADD_LIBRARY(PacMan STATIC ${LOGIC_SRC})


SET(VIEW_SRC
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
        src/events/Event.h
        src/states/StateManager.cpp
        src/states/StateManager.h
        src/view/EntityView.h
        src/view/PacManView.cpp
        src/view/PacManView.h
        src/view/GhostView.cpp
        src/view/GhostView.h
        src/view/WallView.cpp
        src/view/WallView.h
        src/view/CollectableView.cpp
        src/view/CollectableView.h
        src/view/ConcreteFactory.cpp
        src/view/ConcreteFactory.h

)

ADD_EXECUTABLE(Pacman main.cpp ${VIEW_SRC})


TARGET_LINK_LIBRARIES(Pacman PacMan sfml-system sfml-graphics sfml-window)