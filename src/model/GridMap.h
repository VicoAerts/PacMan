/**
 * @file GridMap.h
 * @brief Declaration of the GridMap class holding cells with information representing the game world
 */

#ifndef PACMAN_GRIDMAP_H
#define PACMAN_GRIDMAP_H
#include "../util/Vec2D.h"
#include <fstream>
#include <string>
#include <vector>

/** Enumeration for different cell types in the grid map */
enum CellType { EXIT, EMPTY, WALL, COIN, FRUIT, PACMAN_START, GHOST_START1, GHOST_START2, GHOST_START3, GHOST_START4 };
/** @brief GridMap class representing the game world as a grid of cells with a specific character representing a
 * celltype */
class GridMap {
public:
    /** Default constructor */
    GridMap() = default;
    /** Destructor */
    ~GridMap() = default;
    /** Load maze from file */
    void loadMazeFromFile(const std::string& filename);
    /** Get cell type at given row and column */
    [[nodiscard]] CellType getCellType(int row, int col) const;
    /** Get cell type at given world coordinates */
    [[nodiscard]] CellType getCellType(float worldX, float worldY) const;
    /** Get width of the grid */
    [[nodiscard]] int getWidth() const { return width; }
    /** Get height of the grid */
    [[nodiscard]] int getHeight() const { return height; }
    /** Set cell type at given row and column */
    void setCellType(int row, int col, CellType cellType);
    /** Remove cell type (set to EMPTY) at given row and column */
    void removeCellType(int row, int col);
    /** Convert character from maze to CellType, used in load maze from file */
    CellType charToCellType(char c);
    /** Check if given row and column are within bounds */
    bool inBounds(int row, int col) const;
    /** Get the exit position of the ghost house in world coordinates */
    [[nodiscard]] Vec2D getExitPosition() const;

private:
    /** dimensions of the grid */
    int width, height = 0;
    /** 2D vector representing the grid map */
    std::vector<std::vector<CellType>> grid;
};

#endif // PACMAN_GRIDMAP_H
