/**
 * @file GhostView.h
 * @brief Declaration of the GhostView class which displays ghosts and their changes.
 */
#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "EntityView.h"

namespace view::entity {
class GhostView : public EntityView {
public:
    explicit GhostView(Vec2D startPos, int ghostId);
    /** notify ghost view about changes in model */
    void onNotify(const events::Event& event, model::Entity& entity) override;
    /** draw ghost on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    Vec2D currentPos;
    int ghostId;
    sf::Sprite ghostSprite;
    bool needsUpdate = true;
    Direction currentDir = Direction::None;

    // track animation
    bool isInitialized = false;
    std::vector<sf::IntRect> frames;
    int currentFrameIndex = 0;
    float timer = 0.f;
};
} // namespace view::entity

#endif // PACMAN_GHOSTVIEW_H
