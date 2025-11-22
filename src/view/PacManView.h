/**
 * @file PacManView.h
 * @brief Declaration of the PacManView class which displays pacman and its changes.
 */

#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H
#include "../model/PacMan.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>

namespace view::entity {
class PacManView : public EntityView {
public:
    /** Constructor initializing the PacMan view with its model */
    explicit PacManView(model::PacMan& pacmanModel);
    /** notify pacman view about changes in model */
    void onNotify(const events::Event& event) override;
    /** draw pacman on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;
    /** load pacman texture */

protected:
    model::PacMan& pacmanModel;
    sf::Sprite pacmanSprite;
};
} // namespace view::entity

#endif // PACMAN_PACMANVIEW_H
