//
// Created by gebruiker on 13/12/2025.
//

#include "FruitView.h"
view::entity::FruitView::FruitView(Vec2D startPos) : EntityView(), pos(startPos) {
    fruitSprite = util::TextureManager::getSprite(spriteType::FRUIT, Direction::None);
}
void view::entity::FruitView::onNotify(const events::Event& event, model::Entity& entity) {
    switch (event.type) {
    case events::EventType::FruitEaten:
        isCollected = true;
        break;
    default:
        break;
    }
}
void view::entity::FruitView::draw(sf::RenderWindow& window, Camera& camera) {
    if (!isCollected) {

        auto pixelPos = camera.worldToPixel(pos.x, pos.y);

        float tileW = camera.getTileWidthPixels();
        float tileH = camera.getTileHeightPixels();
        sf::FloatRect bounds = fruitSprite.getLocalBounds();
        float scale = tileH / bounds.height * 0.5f;
        fruitSprite.setScale(scale, scale);
        fruitSprite.setOrigin(bounds.width / 2, bounds.height / 2);
        fruitSprite.setPosition(pixelPos.x, pixelPos.y);

        window.draw(fruitSprite);
    }
}