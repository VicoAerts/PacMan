/**
 * @file PacManView.h
 * @brief Declaration of the PacManView class which displays pacman and its changes.
 */

#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H
#include "../model/PacMan.h"
#include "../util/Clock.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>

namespace view::entity {
class PacManView : public EntityView {
public:
    /** Constructor initializing the PacMan view with its model */
    explicit PacManView(Vec2D startPos, Direction startDir);
    /** notify pacman view about changes in model */
    void onNotify(const events::Event& event, util::Entity& entity) override;
    /** draw pacman on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    Vec2D currentPos;
    Direction currentDir = Direction::None;
    sf::Sprite pacmanSprite;
    bool needsUpdate = true;
    // track animation
    std::vector<sf::IntRect> frames;
    int currentFrameIndex = 0;
    bool isInitialized = false;
    float timer = 0.f;
};
} // namespace view::entity

#endif // PACMAN_PACMANVIEW_H
