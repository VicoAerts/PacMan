//
// Created by gebruiker on 18/11/2025.
//

#include "GhostView.h"

#include <iostream>
view::entity::GhostView::GhostView(Vec2D startPos, int ghostId) : EntityView(), currentPos(startPos), ghostId(ghostId) {
    frames = util::TextureManager::getGhostFrames(currentDir, ghostId);
}
void view::entity::GhostView::onNotify(const events::Event& event, model::Entity& entity) {
    switch (event.type) {
    case events::EventType::PositionChanged:
        currentPos = entity.getPosition();
        needsUpdate = true;
        break;
    case events::EventType::DirectionChanged:
        currentDir = event.direction;
        std::cout << "GhostView::onNotify: Direction changed to " << static_cast<int>(currentDir) << std::endl;
        // update frames for new direction
        frames = util::TextureManager::getGhostFrames(currentDir, ghostId);
        currentFrameIndex = 0;
        timer = 0.f;
        needsUpdate = true;
        break;
    default:
        break;
    }
}
void view::entity::GhostView::draw(sf::RenderWindow& window, Camera& camera) {
    if (!isInitialized) {
        ghostSprite = util::TextureManager::getSprite(spriteType::GHOST, currentDir, ghostId);

        float tileH = camera.getTileHeightPixels();
        sf::FloatRect bounds = ghostSprite.getLocalBounds();
        float scale = tileH / bounds.height * 0.75f;
        ghostSprite.setScale(scale, scale);
        ghostSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        isInitialized = true;
        needsUpdate = true;
    }
    if (frames.empty()) {
        window.draw(ghostSprite);
        std::cerr << "GhostView::draw: No ghost frames found" << std::endl;
    }
    // animation update
    bool isMoving = (previousPos.x != currentPos.x || previousPos.y != currentPos.y);
    if (isMoving) {
        float deltaTime = util::Clock::getInstance()->getDeltaTime();
        timer += deltaTime;
        if (timer >= 0.0001f) {
            // use modulo to cycle through frames
            timer -= 0.0001f;
            currentFrameIndex = (currentFrameIndex + 1) % frames.size();
            ghostSprite.setTextureRect(frames[currentFrameIndex]);
        }
    }

    if (needsUpdate) {
        // update position
        auto pixelPos = camera.worldToPixel(currentPos.x, currentPos.y);
        ghostSprite.setPosition(pixelPos.x, pixelPos.y);
        needsUpdate = false;
    }
    previousPos = currentPos;
    window.draw(ghostSprite);
}