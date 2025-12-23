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
        // update frames for new direction
        if (isFeared) {
            frames = util::TextureManager::getGhostFrames(currentDir, ghostId, 1);
        } else {
            frames = util::TextureManager::getGhostFrames(currentDir, ghostId);
        }
        currentFrameIndex = 0;
        timer = 0.f;
        if (!frames.empty())
            ghostSprite.setTextureRect(frames[0]);
        needsUpdate = true;
        break;
    case events::EventType::GhostModeChanged:
        isFeared = (entity.getCurrentMode() == 1); // 1 is Fear mode
        if (isFeared) {
            frames = util::TextureManager::getGhostFrames(currentDir, ghostId, 1);
        } else {
            frames = util::TextureManager::getGhostFrames(currentDir, ghostId);
        }
        needsUpdate = true;
        currentFrameIndex = 0;
        if (!frames.empty())
            ghostSprite.setTextureRect(frames[0]);

        timer = 0.f;
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
        if (!frames.empty())
            ghostSprite.setTextureRect(frames[0]);
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
        float deltaTime = util::Clock::getInstance().getDeltaTime();
        timer += deltaTime;
        if (timer >= 0.12f) {
            // use modulo to cycle through frames
            timer -= 0.12f;
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