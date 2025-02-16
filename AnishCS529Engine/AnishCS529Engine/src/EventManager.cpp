/*!****************************************************************************
 * \file   EventManager.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * 
 *****************************************************************************/
#include "EventManager.h"

void EventManager::update(float deltaTime) {
  while (
    !delayedEvents.empty() &&
    delayedEvents.top().execTime <= FFramerateController::getController()->getTime()
    ) {
    auto delayedEvent = delayedEvents.top();
    delayedEvents.pop();
    delayedEvent.callback();
  }
}

void EventManager::AddListener(IEventListener* listener) {
  listeners.push_back(listener);
}

void EventManager::RemoveListener(IEventListener* listener) {
  listeners.erase(
      std::remove(listeners.begin(), listeners.end(), listener),
      listeners.end()
  );
}
