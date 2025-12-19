#include "Subject.h"
namespace model {
void Subject::attach(Observer& observer) { observers.push_back(observer); }
void Subject::detach(Observer& observer) {
    auto it = observers.begin();
    while (it != observers.end()) {
        if (&(it->get()) == &observer) {
            it = observers.erase(it);
        } else {
            ++it;
        }
    }
}
void Subject::notify(const events::Event& event, Entity& entity) {
    for (auto& observer : observers) {
        observer.get().onNotify(event, entity);
    }
}

} // namespace model