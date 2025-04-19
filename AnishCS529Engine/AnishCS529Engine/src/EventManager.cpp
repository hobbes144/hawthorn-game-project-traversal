/*!****************************************************************************
 * \file   EventManager.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#include "precompiled.h"
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
