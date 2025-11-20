//
// Created by gebruiker on 20/11/2025.
//

#include "GridMap.h"

void GridMap::loadMazeFromFile(const std::string& filename) {
    std::ifstream file(filename);
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
    case 'G':
        return GHOST_START;
    default:
        return EMPTY;
    }
}
bool GridMap::inBounds(int row, int col) const { return row >= 0 && row < height && col >= 0 && col < width; }
