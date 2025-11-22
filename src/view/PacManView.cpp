//
// Created by gebruiker on 18/11/2025.
//

#include "PacManView.h"
view::entity::PacManView::PacManView(model::PacMan& pacmanModel) : EntityView(pacmanModel), pacmanModel(pacmanModel) {}
void view::entity::PacManView::onNotify(const events::Event& event) {}
void view::entity::PacManView::draw(sf::RenderWindow& window, Camera& camera) {}