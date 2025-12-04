//
// Created by gebruiker on 18/11/2025.
//

#include "GhostView.h"
view::entity::GhostView::GhostView(Vec2D startPos, int ghostId)
    : EntityView(), currentPos(startPos), ghostId(ghostId) {}
void view::entity::GhostView::onNotify(const events::Event& event, model::Entity& entity) {}
void view::entity::GhostView::draw(sf::RenderWindow& window, Camera& camera) {
    if (!isInitialized) {
        ghostSprite = util::TextureManager::getSprite(spriteType::GHOST, currentDir, ghostId);

        float tileH = camera.getTileHeightPixels();
        sf::FloatRect bounds = ghostSprite.getLocalBounds();
        float scale = tileH / bounds.height * 0.75f;
        ghostSprite.setScale(scale, scale);
        ghostSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        isInitialized = true;
        needsUpdate = true;
    }

    if (needsUpdate) {
        // update position
        auto pixelPos = camera.worldToPixel(currentPos.x, currentPos.y);
        ghostSprite.setPosition(pixelPos.x, pixelPos.y);
        needsUpdate = false;
    }
    window.draw(ghostSprite);
}