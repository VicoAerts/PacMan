#include "../view/Camera.h"

#include "../../config/config.h"

#include <cmath>
#include <iostream>
view::Camera::Camera(int windowWidth, int windowHeight) : m_windowHeight(windowHeight), m_windowWidth(windowWidth) {
    resizeWindow(windowWidth, windowHeight);
}

void view::Camera::setGridSize(int rows, int cols) {
    m_rows = (rows > 0 ? rows : 1);
    m_cols = (cols > 0 ? cols : 1);
}
Vec2D view::Camera::worldToPixel(float normX, float normY) const {
    float px = (normX + 1.f) * 0.5f * m_playW;
    float py = (1.f - normY) * 0.5f * m_playH;

    // acount for ui margins if any
    px += config::UI_LEFT;
    py += config::UI_TOP;

    return Vec2D{px, py};
}
Vec2D view::Camera::gridToWorld(int row, int col) const {

    float tileWidth = 2.f / m_cols;
    float tileHeight = 2.f / m_rows;

    float normX = -1.f + tileWidth * (col + 0.5f);
    float normY = 1.f - tileHeight * (row + 0.5f);

    return Vec2D{normX, normY};
}
Vec2D view::Camera::gridToPixel(int row, int col) const {
    Vec2D worldPos = gridToWorld(row, col);
    return worldToPixel(worldPos.x, worldPos.y);
}

float view::Camera::worldWidthToPixels(float worldWidth) const {
    // worldwidth van -1 to 1 is 2 so we need to scale by 0.5
    return worldWidth * 0.5f * m_playW;
}
float view::Camera::worldHeightToPixels(float worldHeight) const { return worldHeight * 0.5f * m_playH; }
float view::Camera::getTileWidthPixels() const {
    float tileWidthWorld = 2.f / m_cols;
    return worldWidthToPixels(tileWidthWorld);
}
float view::Camera::getTileHeightPixels() const {
    float tileHeightWorld = 2.f / m_rows;
    return worldHeightToPixels(tileHeightWorld);
}
void view::Camera::resizeWindow(int width, int height) {
    m_windowWidth = width;
    m_windowHeight = height;

    m_playW = m_windowWidth - (config::UI_LEFT + config::UI_RIGHT);
    m_playH = m_windowHeight - (config::UI_TOP + config::UI_BOTTOM);
}
