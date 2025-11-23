//
// Created by gebruiker on 18/11/2025.
//

#include "WallView.h"

#include <iostream>
view::entity::WallView::WallView(model::Wall& wallModel) : EntityView(wallModel), wallModel(wallModel) {
    // Initialize the wall rectangle shape
    // let the size depend on world size
    wallRect.setFillColor(sf::Color::Blue);
}
void view::entity::WallView::onNotify(const events::Event& event) {}
void view::entity::WallView::draw(sf::RenderWindow& window, Camera& camera) {
    Vec2D worldPos = wallModel.getPosition();
    Vec2D pixelPos = camera.worldToPixel(worldPos.x, worldPos.y);

    // how many pixels per tile
    float width = camera.getTileWidthPixels();
    float height = camera.getTileHeightPixels();

    wallRect.setSize(sf::Vector2f(width, height));
    wallRect.setOrigin(width / 2.f, height / 2.f);
    wallRect.setPosition(pixelPos.x, pixelPos.y);

    window.draw(wallRect);
}