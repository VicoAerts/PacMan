/**
 * @file Observer.h
 * @brief Declaration of the Observer interface for observer pattern. Observer is gate between Model and View.
 */

#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H
#include "../events/Event.h"

namespace model {
class Subject;
class Entity;

/**
 * @brief Observer interface for receiving game events.
 */
class Observer {
public:
    /** Virtual destructor */
    virtual ~Observer() = default;

    /** pure virtual function called by subject when event happens */
    virtual void onNotify(const events::Event& event, Entity& entity) = 0;
};
} // namespace model

#endif // PACMAN_OBSERVER_H
