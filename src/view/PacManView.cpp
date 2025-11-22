//
// Created by gebruiker on 18/11/2025.
//

#include "PacManView.h"
view::entity::PacManView::PacManView(model::PacMan& pacmanModel) : EntityView(pacmanModel), pacmanModel(pacmanModel) {
    pacmanSprite = util::TextureManager::getSprite(spriteType::PACMAN, pacmanModel.getDirection());
}
void view::entity::PacManView::onNotify(const events::Event& event) {}
void view::entity::PacManView::draw(sf::RenderWindow& window, Camera& camera) {
    auto worldPos = pacmanModel.getPosition();
    auto pixelPos = camera.worldToPixel(worldPos.x, worldPos.y);

    Direction dir = pacmanModel.getDirection();
    pacmanSprite = util::TextureManager::getSprite(spriteType::PACMAN, dir);
    pacmanSprite.setPosition(pixelPos.x, pixelPos.y);

    window.draw(pacmanSprite);
}
