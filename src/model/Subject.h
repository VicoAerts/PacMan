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
#include <vector>

namespace util {
class Subject {
private:
    /** subject holds references to all observers, we use reference wrapper because normal pointers Observer* is not
     * allowed*/
    std::vector<std::reference_wrapper<Observer>> observers;

public:
    /** attach observer to subject */
    void attach(Observer& observer);

    /** detach observer from subject */
    void detach(Observer& observer);

protected:
    /** notify observer about event */
    void notify(const events::Event& event, Entity& entity);
};
} // namespace model

#endif // PACMAN_SUBJECT_H
