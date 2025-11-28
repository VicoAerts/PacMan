//
// Created by gebruiker on 18/11/2025.
//

#include "PacManView.h"

#include <iostream>
view::entity::PacManView::PacManView(Vec2D startPos, Direction startDir)
    : EntityView(), currentPos(startPos), currentDir(startDir) {}
void view::entity::PacManView::onNotify(const events::Event& event, model::Entity& enitity) {
    switch (event.type) {
    case events::EventType::PositionChanged:
        currentPos = enitity.getPosition();
        needsUpdate = true;
        break;
    case events::EventType::DirectionChanged:
        currentDir = event.direction;
        break;
    default:
        break;
    }
}
void view::entity::PacManView::draw(sf::RenderWindow& window, Camera& camera) {
    // only do calculations if model changed
    if (needsUpdate) {
        auto pixelPos = camera.worldToPixel(currentPos.x, currentPos.y);

        pacmanSprite = util::TextureManager::getSprite(spriteType::PACMAN, currentDir);

        float tileW = camera.getTileWidthPixels();
        float tileH = camera.getTileHeightPixels();

        sf::FloatRect bounds = pacmanSprite.getLocalBounds();

        float scale = tileH / bounds.height * 0.75f;
        pacmanSprite.setScale(scale, scale);
        pacmanSprite.setOrigin(bounds.width / 2, bounds.height / 2);

        pacmanSprite.setPosition(pixelPos.x, pixelPos.y);
        needsUpdate = false;
    }

    window.draw(pacmanSprite);
}
