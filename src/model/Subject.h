/**
 * @file Subject.h
 * @brief Base class for all observable objects in the model.
 *
 * The Subject class manages observer registration and event notification,
 * forming the foundation of the Observer pattern used throughout the game.
 */

#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Observer.h"
#include <functional>
#include <memory>
#include <vector>

namespace model {
class Entity;
/** @brief Subject base class for observer pattern */
class Subject {
private:
    /** subject holds references to all observers*/
    std::vector<std::weak_ptr<Observer>> observers;

public:
    /** attach observer to subject */
    void attach(std::shared_ptr<Observer> observer);

    /** detach observer from subject */
    void detach(std::shared_ptr<Observer> observer);

protected:
    /** notify observer about event */
    void notify(const events::Event& event, Entity& entity);
};
} // namespace model

#endif // PACMAN_SUBJECT_H
