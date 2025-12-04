//
// Created by gebruiker on 20/11/2025.
//

#include "GridMap.h"

#include <cmath>

void GridMap::loadMazeFromFile(const std::string& filename) {
    std::ifstream file("../config/" + filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    if (lines.empty()) {
        throw std::runtime_error("File: " + filename + " is empty");
    }
    // Set dimensions
    // Assuming all lines have the same length and height is number of lines
    height = lines.size();
    width = lines[0].length();
    // Resize grid
    grid.resize(height, std::vector<CellType>(width, EMPTY));
    // Fill grid
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            grid[row][col] = charToCellType(lines[row][col]);
        }
    }
}

CellType GridMap::getCellType(int row, int col) const {
    if (!inBounds(row, col)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return grid[row][col];
}
CellType GridMap::getCellType(float worldX, float worldY) const {
    const float tileWidth = 2.f / static_cast<float>(width);
    const float tileHeight = 2.f / static_cast<float>(height);

    float colF = (worldX + 1.f) / tileWidth;
    float rowF = (1.f - worldY) / tileHeight;
    int col = static_cast<int>(std::floor(colF));
    int row = static_cast<int>(std::floor(rowF));

    if (!inBounds(row, col)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return grid[row][col];
}

void GridMap::setCellType(int row, int col, CellType cellType) {
    if (!inBounds(row, col)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    grid[row][col] = cellType;
}

void GridMap::removeCellType(int row, int col) {
    if (!inBounds(row, col)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    grid[row][col] = EMPTY;
}

CellType GridMap::charToCellType(char c) {
    switch (c) {
    case '#':
        return WALL;
    case '.':
        return COIN;
    case 'F':
        return FRUIT;
    case 'P':
        return PACMAN_START;
    case '1':
        return GHOST_START1;
    case '2':
        return GHOST_START2;
    case '3':
        return GHOST_START3;
    case '4':
        return GHOST_START4;
    default:
        return EMPTY;
    }
}
bool GridMap::inBounds(int row, int col) const { return row >= 0 && row < height && col >= 0 && col < width; }
