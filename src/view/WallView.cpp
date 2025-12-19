#include "WallView.h"

#include <iostream>
view::entity::WallView::WallView(Vec2D startPos) : EntityView(), pos(startPos) {
    // Initialize the wall rectangle shape
    // let the size depend on world size
    wallRect.setFillColor(sf::Color::Blue);
}
void view::entity::WallView::onNotify(const events::Event& event,
                                      model::Entity& enitity) { // no need to handle events for static wall}
}
void view::entity::WallView::draw(sf::RenderWindow& window, Camera& camera) {

    Vec2D pixelPos = camera.worldToPixel(pos.x, pos.y);

    // how many pixels per tile
    float width = camera.getTileWidthPixels();
    float height = camera.getTileHeightPixels();

    wallRect.setSize(sf::Vector2f(width, height));
    wallRect.setOrigin(width / 2.f, height / 2.f);
    wallRect.setPosition(pixelPos.x, pixelPos.y);

    window.draw(wallRect);
}