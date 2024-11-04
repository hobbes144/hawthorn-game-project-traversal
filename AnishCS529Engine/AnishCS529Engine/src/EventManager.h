/*!****************************************************************************
 * \file   EventManager.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * \brief  Event Manager system that allows components to interact with each 
 * other.
 * 
 *****************************************************************************/
#ifndef EVENT_MANAGER_H
#pragma once

#include "Event.h"
#include "EventListener.h"

#include <vector>

class EventManager {
public:
  static EventManager& Instance() {
    static EventManager instance;
    return instance;
  }

  void addListener(IEventListener* listener);

  void removeListener(IEventListener* listener);

  template <typename T>
  void broadcastEvent(const T& event) {
    for (auto listener : listeners) {
      listener->handleEvent(event);
    }
  }

private:
  EventManager() = default;
  std::vector<IEventListener*> listeners;
};

#endif // EVENT_MANAGER_H
