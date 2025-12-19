#include "Subject.h"
namespace model {
void Subject::attach(std::shared_ptr<Observer> observer) { observers.push_back(observer); }
void Subject::detach(std::shared_ptr<Observer> observer) {
    auto it = observers.begin();
    while (it != observers.end()) {
        // lock the weak_ptr to compare with observer
        if (it->lock() == observer) {
            it = observers.erase(it);
        } else {
            ++it;
        }
    }
}
void Subject::notify(const events::Event& event, Entity& entity) {
    for (auto it = observers.begin(); it != observers.end();) {
        // check if observer still exists
        if (auto observerPtr = it->lock()) {
            observerPtr->onNotify(event, entity);
            ++it;
        } else {
            // remove expired observer
            it = observers.erase(it);
        }
    }
}

} // namespace model