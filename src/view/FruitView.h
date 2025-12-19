/*
 *@file FruitView.h
 *@brief Declaration of the Fruitview class which displays the fruits.
 */

#ifndef PACMAN_FRUITVIEW_H
#define PACMAN_FRUITVIEW_H
#include "EntityView.h"

namespace view::entity {
/** @brief View class for rendering Fruit entities. */
class FruitView : public EntityView {
public:
    /** Constructor initializing the Fruit view */
    explicit FruitView(Vec2D startPos);
    /** notify fruit view about changes in model */
    void onNotify(const events::Event& event, model::Entity& entity) override;
    /** draw fruit on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    Vec2D pos;
    bool isCollected = false;
    sf::Sprite fruitSprite;
};
} // namespace view::entity

#endif // PACMAN_FRUITVIEW_H
