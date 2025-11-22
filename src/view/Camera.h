/**
 *@file Camera.h
 *@brief camera class will translate world coordinates and sizes to screen coordinates and vice versa
 *we will first normalise the coordinates of the world in an [-1`,1] range and then scale them to the screen size
 *we will need window width and height for that
 */

#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H
/** 2D Vector structure */
#include "../util/Vec2D.h"

namespace view {
class Camera {
public:
    /** camera constructor using window width and height*/
    Camera(int windowWidth, int windowHeight);

    /** update window size (for example when window is resized)*/
    void setWindowSize(int windowWidth, int windowHeight);

    /** set world size (for example when level is changed)*/
    void setGridSize(int rows, int cols);

    /** convert world normalised coords to pixels*/
    [[nodiscard]] Vec2D worldToPixel(float normX, float normY) const;

    /**gridToWorld converts grid coordinates to world normalised coordinates*/
    [[nodiscard]] Vec2D gridToWorld(int row, int col) const;

    /** gridmap to pixel converts grid coordinates to pixel coordinates*/
    [[nodiscard]] Vec2D gridToPixel(int row, int col) const;

    /** world width in pixels to calculate the size of sprites*/
    [[nodiscard]] float worldWidthToPixels(float worldWidth) const;

    /** world height in pixels to calculate the size of sprites*/
    [[nodiscard]] float worldHeightToPixels(float worldHeight) const;

private:
    int m_windowWidth;
    int m_windowHeight;

    /** row and column count of the world grid*/
    int m_rows;
    int m_cols;
};
} // namespace view

#endif // PACMAN_CAMERA_H
