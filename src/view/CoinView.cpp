//
// Created by gebruiker on 23/11/2025.
//

#include "CoinView.h"

#include <iostream>
view::entity::CoinView::CoinView(Vec2D startPos) : EntityView(), pos(startPos) {
    coinSprite = util::TextureManager::getSprite(spriteType::COIN, Direction::None);
}
void view::entity::CoinView::onNotify(const events::Event& event, model::Entity& enitity) {}
void view::entity::CoinView::draw(sf::RenderWindow& window, Camera& camera) {

    if (!isCollected) {
        std::cout << "CoinView::draw" << !isCollected << std::endl;

        auto pixelPos = camera.worldToPixel(pos.x, pos.y);

        float tileW = camera.getTileWidthPixels();
        float tileH = camera.getTileHeightPixels();
        sf::FloatRect bounds = coinSprite.getLocalBounds();
        float scale = tileH / bounds.height * 0.7f;
        coinSprite.setScale(scale, scale);
        coinSprite.setOrigin(bounds.width / 2, bounds.height / 2);
        coinSprite.setPosition(pixelPos.x, pixelPos.y);

        window.draw(coinSprite);
    }
}