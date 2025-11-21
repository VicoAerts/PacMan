//
// Created by gebruiker on 17/11/2025.
//

#include "../view/Camera.h"
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
    float x = (normX + 1.f) * 0.5f * m_windowWidth;
    float y = m_windowHeight - (normY + 1.f) * 0.5f * m_windowHeight;
    return Vec2D{x, y};
}
Vec2D view::Camera::gridToWorld(int row, int col) const {
    // normalizing
    float normX = -1.f + 2.f * (col + 0.5f) / m_cols;
    float normY = 1.f - 2.f * (row + 0.5f) / m_rows;
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