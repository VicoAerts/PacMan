//
// Created by gebruiker on 17/11/2025.
//

#include "../view/Camera.h"

#include <cmath>
#include <iostream>
view::Camera::Camera(int windowWidth, int windowHeight) : m_windowHeight(windowHeight), m_windowWidth(windowWidth) {}
void view::Camera::setWindowSize(int windowWidth, int windowHeight) {
    m_windowHeight = windowHeight;
    m_windowWidth = windowWidth;
}
void view::Camera::setGridSize(int rows, int cols) {
    m_rows = (rows > 0 ? rows : 1);
    m_cols = (cols > 0 ? cols : 1);
}
Vec2D view::Camera::worldToPixel(float normX, float normY) const {
    float px = (normX + 1.f) * 0.5f * m_windowWidth;
    float py = (1.f - normY) * 0.5f * m_windowHeight;

    // std::cout << "[worldToPixel] norm=(" << normX << ", " << normY << ")" << " | pixel=(" << px << ", " << py << ")"
    //           << std::endl;

    return Vec2D{px, py};
}
Vec2D view::Camera::gridToWorld(int row, int col) const {

    float tileWidth = 2.f / m_cols;
    float tileHeight = 2.f / m_rows;

    float normX = -1.f + tileWidth * (col + 0.5f);
    float normY = 1.f - tileHeight * (row + 0.5f);
    // std::cout << "[gridToWorld] row=" << row << " col=" << col << " | world=(" << normX << ", " << normY << ")"
    //           << std::endl;

    return Vec2D{normX, normY};
}
Vec2D view::Camera::gridToPixel(int row, int col) const {
    Vec2D worldPos = gridToWorld(row, col);
    return worldToPixel(worldPos.x, worldPos.y);
}

float view::Camera::worldWidthToPixels(float worldWidth) const {
    // worldwidth van -1 to 1 is 2 so we need to scale by 0.5
    return worldWidth * 0.5f * m_windowWidth;
}
float view::Camera::worldHeightToPixels(float worldHeight) const { return worldHeight * 0.5f * m_windowHeight; }
float view::Camera::getTileWidthPixels() const {
    float tileWidthWorld = 2.f / m_cols;
    return worldWidthToPixels(tileWidthWorld);
}
float view::Camera::getTileHeightPixels() const {
    float tileHeightWorld = 2.f / m_rows;
    return worldHeightToPixels(tileHeightWorld);
}
