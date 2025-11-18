/**
 *@file Entity.h
 *@brief Base class for all entities in the game model.
 */

#ifndef PACMAN_ENITYMODEL_H
#define PACMAN_ENITYMODEL_H
namespace model {
/** Forward declaration of World class */
class World;

/** 2D Vector structure */
struct Vec2D {
    float x = {0.f};
    float y = {0.f};
};

class Entity {
protected:
    /** Constructor to initialize entity on position */
    explicit Entity(const Vec2D& pos) : m_position(pos) {}
    /** Position of the entity itself so member position in 2D space  */
    Vec2D m_position;

private:
    /** Entity destructor */
    virtual ~Entity() = default;

    /**update entity*/
    virtual void update(const double deltaTime, World& world) = 0;

    /** get position of entity */
    [[nodiscard]] Vec2D getPosition() const { return m_position; }

    /** set position of entity */
    void setPosition(const Vec2D& pos) { m_position = pos; }
};
} // namespace model
#endif // PACMAN_ENITYMODEL_H
