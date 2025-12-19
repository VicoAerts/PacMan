/**
 * @file GhostView.h
 * @brief Declaration of the GhostView class which displays ghosts and their changes.
 */
#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "../util/Clock.h"
#include "EntityView.h"

namespace view::entity {
/** @brief View class for rendering Ghost entities. */
class GhostView : public EntityView {
public:
    /** Constructor initializing the Ghost view and gets the frames from texture manager */
    explicit GhostView(Vec2D startPos, int ghostId);
    /** notify ghost view about changes in model */
    void onNotify(const events::Event& event, model::Entity& entity) override;
    /** draw ghost on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    Vec2D currentPos;
    Vec2D previousPos;
    int ghostId;
    sf::Sprite ghostSprite;
    bool needsUpdate = true;
    Direction currentDir = Direction::None;
    bool isFeared = false;

    // track animation
    bool isInitialized = false;
    std::vector<sf::IntRect> frames;
    int currentFrameIndex = 0;
    float timer = 0.f;
};
} // namespace view::entity

#endif // PACMAN_GHOSTVIEW_H
