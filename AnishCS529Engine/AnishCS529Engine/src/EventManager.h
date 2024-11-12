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
#pragma once

#include "Event.h"
#include "EventListener.h"

#include <vector>

 // Event Manager - Singleton pattern
class EventManager {
public:
  static EventManager& Instance() {
    static EventManager instance;
    return instance;
  }

  // Simple version - just store all listeners in a vector
  //void AddListener(EventListener<Event>* listener);
  void AddListener(IEventListener* listener);

  //void RemoveListener(EventListener<Event>* listener);
  void RemoveListener(IEventListener* listener);

  // Broadcast event to interested listeners
  template<typename T>
  void BroadcastEvent(const T& event) {
    for (auto listener : listeners) {
      listener->HandleEvent(event);
    }
  }

private:
  EventManager() = default;
  std::vector<IEventListener*> listeners;
};