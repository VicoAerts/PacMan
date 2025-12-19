#include "PacManView.h"

#include <iostream>
view::entity::PacManView::PacManView(Vec2D startPos, Direction startDir)
    : EntityView(), currentPos(startPos), currentDir(startDir), previousPos(startPos) {
    frames = util::TextureManager::getPacManFrames(currentDir);
}
void view::entity::PacManView::onNotify(const events::Event& event, model::Entity& entity) {
    switch (event.type) {
    case events::EventType::PositionChanged:
        currentPos = entity.getPosition();
        needsUpdate = true;
        break;
    case events::EventType::DirectionChanged:
        currentDir = event.direction;
        // update frames for new direction
        frames = util::TextureManager::getPacManFrames(currentDir);
        currentFrameIndex = 0;
        timer = 0.f;
        needsUpdate = true;
        break;
    default:
        break;
    }
}
void view::entity::PacManView::draw(sf::RenderWindow& window, Camera& camera) {
    // only do calculations if model changed
    if (!isInitialized) {
        pacmanSprite = util::TextureManager::getSprite(spriteType::PACMAN, currentDir);

        float tileH = camera.getTileHeightPixels();
        sf::FloatRect bounds = pacmanSprite.getLocalBounds();
        float scale = tileH / bounds.height * 0.75f;
        pacmanSprite.setScale(scale, scale);
        pacmanSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        isInitialized = true;
        needsUpdate = true;
    }
    if (frames.empty()) {
        window.draw(pacmanSprite);
    }
    bool isMoving = (previousPos.x != currentPos.x || previousPos.y != currentPos.y);

    if (isMoving) {
        // animation update if moving
        float deltaTime = util::Clock::getInstance().getDeltaTime();
        timer += deltaTime;

        if (timer >= 0.0001f) {
            // use modulo to cycle through frames
            timer -= 0.0001f;
            currentFrameIndex = (currentFrameIndex + 1) % frames.size();
        }
    }
    pacmanSprite.setTextureRect(frames[currentFrameIndex]);

    if (needsUpdate) {
        auto pixelPos = camera.worldToPixel(currentPos.x, currentPos.y);
        pacmanSprite.setPosition(pixelPos.x, pixelPos.y);
        needsUpdate = false;
    }

    previousPos = currentPos;
    window.draw(pacmanSprite);
}
