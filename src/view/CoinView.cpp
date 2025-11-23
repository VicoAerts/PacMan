//
// Created by gebruiker on 23/11/2025.
//

#include "CoinView.h"

#include <iostream>
view::entity::CoinView::CoinView(model::Coin& coinModel) : EntityView(coinModel), coinModel(coinModel) {
    coinSprite = util::TextureManager::getSprite(spriteType::COIN);
}
void view::entity::CoinView::onNotify(const events::Event& event) {}
void view::entity::CoinView::draw(sf::RenderWindow& window, Camera& camera) {
    auto worldPos = coinModel.getPosition();
    auto pixelPos = camera.worldToPixel(worldPos.x, worldPos.y);

    float tileW = camera.getTileWidthPixels();
    float tileH = camera.getTileHeightPixels();
    sf::FloatRect bounds = coinSprite.getLocalBounds();
    float scale = tileH / bounds.height * 0.7f;
    coinSprite.setScale(scale, scale);
    coinSprite.setOrigin(bounds.width / 2, bounds.height / 2);
    coinSprite.setPosition(pixelPos.x, pixelPos.y);

    window.draw(coinSprite);
}