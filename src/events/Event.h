/**
 *file Event.h
 *brief event class for all custom events
 */
#ifndef PACMAN_EVENT_H
#define PACMAN_EVENT_H
#include "../util/Direction.h"
#include <memory>
#include <optional>

/* Forward declaration */
namespace model {
class Entity;
}

/* Event namespace */
namespace events {

/* Event types enumeration */
enum class EventType { Tick, PositionChanged, DirectionChanged, CoinEaten, FruitEaten, PacManDied, GhostEaten, None };

/* Event class definition */
class Event {
public:
    /* Event type */
    EventType type;
    /* optional direction associated with the event */
    Direction direction;

    /* Constructor that makes event depending on the type and the entity that triggered the event */
    Event(EventType t, Direction direction = Direction::None) : type(t), direction(direction){};
};

} // namespace events

#endif // PACMAN_EVENT_H
