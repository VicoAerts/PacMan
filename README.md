# PacMan (SFML, C++) (20230569)

An SFML-based Pac-Man clone with a clear separation between logic (static library) and rendering (executable). The
project follows the coursework requirements (advanced programming UAntwerp): MVC separation, Observer/Abstract
Factory/State/Singleton patterns, normalized world coordinates with a camera, a multi-state flow (menu → level →
victory/pause/game-over) and the use of smart pointers only.

## Build & Run

1. Prerequisites: CMake ≥ 3.22, SFML 2.6, C++17 compiler (tested with GCC/Clang from the course environment).
2. Configure & build:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build . -j
   ```
3. Run:
   ```bash
   ./Pacman  
   ```

## Controls

- **Arrow keys**: Move Pac-Man (continuous movement; follows last valid input).
- **Enter**: From menu → start game; from victory → next level. From game over → back to menu.
- **Esc**: Pause (from level); from game over → close game.
- **K**: Debug – clear collectables (development aid to go through levels faster).
- Mouse click on the start button in the menu also starts the game.

## Gameplay Loop

1. Menu shows top 5 scores and start button.
2. Level loads maze from `config/Maze.txt`(maze can be loaded from different file if you change this), spawns Pac-Man,
   four ghosts, coins, and fruits.
3. Coins increase score with a time-based bonus; score decays over time.
4. Fruits trigger fear mode (ghost slowdown + reverse) and grant extra points by eating them.
5. Lives: 3; collision with an unfeared ghost removes a life and resets entities.
6. Level clear: all collectables eaten → Victory screen → Enter to next level.
7. Game over: lives exhausted → GameOver screen, high scores saved.

## Evaluation Checklist (for course)

- [x] **Startup screen + scoreboard** – menu with top 5 scores and start button (`src/states/MenuState.*`).
- [x] **Maze & collision correctness** – grid-loaded maze, wall collision checks with hitbox corners (`config/Maze.txt`,
  `src/control/World::isMoveValid`).
- [x] **Smooth continuous movement** – Pac-Man/ghosts move with delta time and corridor snapping to provide smooth
  cornering (
  `src/model/PacMan.cpp`, `src/model/Ghost.cpp`).
- [x] **Ghost movement & AI** – four ghosts with spawn delays, chase/leave/fear modes; random, facing, and direct-chase
  behaviors (`src/model/Ghost.cpp`).
- [x] **Score modifiers (coins/fruits/ghosts) & decay** – time-based coin bonus, fruit bonus, ghost eating chain bonus,
  time
  decay (`src/model/Score.cpp`).
- [x] **Fear mode + ghost reversal** – fruit triggers fear with slowdown, reverse/away-from target choice (
  `src/control/World.cpp`, `src/model/Ghost.cpp`).
- [x] **Level clearing + scaling difficulty** – level counter, speed/fear scaling per level difficulty increase gets
  capped after certain level to maintain playability, Victory screen before next
  level (`src/states/LevelState.cpp`, `src/view/ConcreteFactory.cpp`, `src/states/VictoryState.cpp`).
- [x] **Lives & game over** – 3 lives, reset on death, GameOver state with restart/quit (`src/model/Score.cpp`,
  `src/states/GameOverState.cpp`).
- [x] **MVC separation & logic library** – logic compiled into `PacMan` static lib, SFML-only in view (`CMakeLists.txt`,
  `src/model/*`, `src/view/*`).
- [x] **Design patterns** – State (state stack), Observer (model ↔ view/score), Abstract Factory (entity creation with
  views attached), Singletons (Clock, Random), MVC (`src/states/*`, `src/model/Subject/Observer.*`,
  `src/view/ConcreteFactory.*`, `src/util/Clock.cpp`, `src/util/Random.h`).
- [x] **Camera & normalized coordinates** –grid coordinates, projection to world coordinates in [-1,1], projection to
  pixels on window (`src/view/Camera.*`).

## Assets & Data

- Sprites: `assets/sprites.png`
- Menu background: `assets/pacmenu.png`
- Maze: `config/Maze.txt` (2nd maze `Maze1.txt` available)
- High scores: `config/HighScores.txt` (created/updated on game over)
## Defence Video

The defence video provides a short gameplay demonstration followed by an explanation of the main design and
architectural choices of the project. The focus lies on the applied design patterns, MVC separation, ownership and
lifetime management using smart pointers, and the overall code structure.

▶️ https://youtu.be/52VKaClNPug  

*My apologies that the video is slightly longer than intended.*




