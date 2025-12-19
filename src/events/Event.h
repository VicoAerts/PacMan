/**
 *@file Event.h
 *@brief event class for all custom events used in the game.
 *Supports the observer pattern for notifying entities about events.
 */
#ifndef PACMAN_EVENT_H
#define PACMAN_EVENT_H
#include "../util/Direction.h"

namespace model {
class Entity;
}

/** Namespace for all event-related classes and enumerations */
namespace events {

/** Event types enumeration processed and used by all observer patterns */
enum class EventType {
    Tick,
    PositionChanged,
    DirectionChanged,
    CoinEaten,
    FruitEaten,
    PacManDied,
    GhostModeChanged,
    GhostEaten,
    None
};

/** Event class definition */
class Event {
public:
    /** Event type */
    EventType type;
    /** direction associated with the event, if the event has nothing to do with direction it will be set to None*/
    Direction direction;

    /** Constructor that makes event depending on the type and the entity that triggered the event */
    Event(EventType t, Direction direction = Direction::None) : type(t), direction(direction){};
};

} // namespace events

#endif // PACMAN_EVENT_H
