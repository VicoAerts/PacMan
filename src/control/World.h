/**
 * @file World.h
 * @brief holds all entities, orchestration of game logic and interaction between entities
 */

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "../model/AbstractFactory.h"
#include "../model/Entity.h"
#include "../model/GridMap.h"
#include "../model/PacMan.h"
#include "../util/Direction.h"
#include "../util/Random.h"

#include <memory>
#include <vector>

namespace model {
class Score;
class World {
public:
    /**constructor for world taking a gridmap and a factory to spawn entities*/
    World(const GridMap& map, AbstractFactory& factory, Score& playerScore);
    /**update all entities in the world*/
    void update(double deltaTime);
    /**get the gridmap of the world*/
    [[nodiscard]] const GridMap& getGridMap() const { return worldGrid; }
    /**handle input for pacman*/
    void handleInput(Direction dir);
    /** check if move is valid in the gridmap*/
    bool isMoveValid(const Vec2D& position, const Vec2D& step, const Entity& entity) const;
    /** let snap to corridor/center of tile*/
    void snapToCorridor(Vec2D& pos, const Direction dir) const;
    /** collect collectable at position*/
    void handlePacManCollisions(const Vec2D& pos);
    /** get pacman entity*/
    Entity& getPacMan() const;
    /** reset world if pacman loses a life*/
    void resetWorld();
    /** isWorldCleared*/
    bool isWorldCleared() const;
    /** debug clear all collectables*/
    void debugClearCollectables();
    /**rng for the world*/
    util::Random rng;
    /** get current level*/
    [[nodiscard]] int getCurrentLevel() const { return currentLevel; }

private:
    GridMap worldGrid;
    // Other members like entities, score, lives, etc.
    std::vector<std::unique_ptr<Entity>> entities;
    std::unique_ptr<PacMan> pacMan;
    Score& score;
    int m_remainingCollectables;
    int currentLevel;
    void spawnEntities(AbstractFactory& factory);
};
} // namespace model
#endif // PACMAN_WORLD_H
