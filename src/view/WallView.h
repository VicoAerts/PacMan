/**
 * @file WallView.h
 * @brief Declaration of the WallView class which displays the walls.
 */

#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H
#include "../model/Wall.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
namespace view::entity {
/** @brief WallView class responsible for rendering Wall entity */
class WallView : public EntityView {
public:
    /** Constructor initializing the Wall view with its model */
    explicit WallView(Vec2D pos);
    /** notify wall view about changes in model currently not used */
    void onNotify(const events::Event& event, model::Entity& entity) override;
    /** draw wall on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    Vec2D pos;
    sf::RectangleShape wallRect;
};
} // namespace view::entity

#endif // PACMAN_WALLVIEW_H
