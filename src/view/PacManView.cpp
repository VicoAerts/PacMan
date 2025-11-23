//
// Created by gebruiker on 18/11/2025.
//

#include "PacManView.h"

#include <iostream>
view::entity::PacManView::PacManView(model::PacMan& pacmanModel) : EntityView(pacmanModel), pacmanModel(pacmanModel) {
    pacmanSprite = util::TextureManager::getSprite(spriteType::PACMAN, pacmanModel.getDirection());
}
void view::entity::PacManView::onNotify(const events::Event& event) {}
void view::entity::PacManView::draw(sf::RenderWindow& window, Camera& camera) {
    auto worldPos = pacmanModel.getPosition();
    auto pixelPos = camera.worldToPixel(worldPos.x, worldPos.y);

    Direction dir = pacmanModel.getDirection();
    pacmanSprite = util::TextureManager::getSprite(spriteType::PACMAN, dir);

    float tileW = camera.getTileWidthPixels();
    float tileH = camera.getTileHeightPixels();

    sf::FloatRect bounds = pacmanSprite.getLocalBounds();

    float scale = tileH / bounds.height * 0.75f;
    pacmanSprite.setScale(scale, scale);
    pacmanSprite.setOrigin(bounds.width / 2, bounds.height / 2);

    pacmanSprite.setPosition(pixelPos.x, pixelPos.y);

    window.draw(pacmanSprite);
}
