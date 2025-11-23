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
class WallView : public EntityView {
public:
    /** Constructor initializing the Wall view with its model */
    explicit WallView(model::Wall& wallModel);
    /** notify wall view about changes in model */
    void onNotify(const events::Event& event) override;
    /** draw wall on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    model::Wall& wallModel;
    sf::RectangleShape wallRect;
};
} // namespace view::entity

#endif // PACMAN_WALLVIEW_H
