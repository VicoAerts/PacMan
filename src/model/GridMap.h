/**
 * @file GridMap.h
 * @brief Declaration of the GridMap class holding cells with information representing the game world
 */

#ifndef PACMAN_GRIDMAP_H
#define PACMAN_GRIDMAP_H
#include "../util/Vec2D.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

enum CellType { EXIT, EMPTY, WALL, COIN, FRUIT, PACMAN_START, GHOST_START1, GHOST_START2, GHOST_START3, GHOST_START4 };
class GridMap {
public:
    GridMap() = default;
    ~GridMap() = default;

    void loadMazeFromFile(const std::string& filename);

    [[nodiscard]] CellType getCellType(int row, int col) const;

    [[nodiscard]] CellType getCellType(float worldX, float worldY) const;

    [[nodiscard]] int getWidth() const { return width; }

    [[nodiscard]] int getHeight() const { return height; }

    void setCellType(int row, int col, CellType cellType);

    void removeCellType(int row, int col);

    CellType charToCellType(char c);

    bool inBounds(int row, int col) const;

    // Voeg deze declaratie toe
    [[nodiscard]] Vec2D getExitPosition() const;

private:
    /** dimensions of the grid */
    int width, height;

    /** 2D vector representing the grid map */
    std::vector<std::vector<CellType>> grid;
};

#endif // PACMAN_GRIDMAP_H
