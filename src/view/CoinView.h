/*
 *@file CoinView.h
 *@brief Declaration of the CoinView class which displays the coins.
 */

#ifndef PACMAN_COINVIEW_H
#define PACMAN_COINVIEW_H
#include "../model/Coin.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
namespace view::entity {
class CoinView : public EntityView {
public:
    /** Constructor initializing the Coin view with its model */
    explicit CoinView(Vec2D startPos);
    /** notify coin view about changes in model */
    void onNotify(const events::Event& event, model::Entity& entity) override;
    /** draw coin on screen */
    void draw(sf::RenderWindow& window, Camera& camera) override;

private:
    Vec2D pos;
    bool isCollected = false;
    sf::Sprite coinSprite;
};
} // namespace view::entity

#endif // PACMAN_COINVIEW_H
