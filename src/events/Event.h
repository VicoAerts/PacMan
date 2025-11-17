/**
 *file Event.h
 *brief event class for all custom events
 */
#ifndef PACMAN_EVENT_H
#define PACMAN_EVENT_H
#include <memory>

/* Forward declaration */
namespace model {
class EntityModel;
}

/* Event namespace */
namespace events {

/* Event types enumeration */
enum class EventType { Tick, PositionChanged, DirectionChanged, CoinEaten, FruitEaten, PacManDied, GhostEaten };

/* Event class definition */
class Event {
public:
    /* Event type */
    EventType type;
    /* Entity that triggered event */
    std::shared_ptr<model::EntityModel> entity;

    /* Constructor that makes event depending on the type and the entity that triggered the event */
    Event(EventType t, std::shared_ptr<model::EntityModel> e = nullptr) : type(t), entity(std::move(e)) {}
};

} // namespace events

#endif // PACMAN_EVENT_H
