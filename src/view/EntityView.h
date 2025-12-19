/**
 * @file EntityView.h
 * @brief Base class for all entity views in the game.
 */

#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "../model/Entity.h"
#include "../util/TextureManager.h"
#include "Camera.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace view::entity {
/** Abstract base class for all entity views. */
class EntityView : public model::Observer {

public:
    /** Constructor initializing the entity view with its model */
    EntityView() = default;
    /** Virtual destructor */
    virtual ~EntityView() = default;
    /** Pure virtual draw method to be implemented by derived classes */
    virtual void draw(sf::RenderWindow& window, Camera& camera) = 0;
};
} // namespace view::entity

#endif // PACMAN_ENTITYVIEW_H
