#include "EventManager.h"

void EventManager::AddListener(IEventListener* listener){
    listeners.push_back(listener);
}

void EventManager::RemoveListener(IEventListener* listener){
    listeners.erase(
        std::remove(listeners.begin(), listeners.end(), listener),
        listeners.end()
    );
}
