/*!****************************************************************************
 * \file   EventListener.inl
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * \brief  Event listener implementation for templated functionality.
 * 
 *****************************************************************************/
 // EventListener template implementations (after EventManager definition)
#ifndef EVENT_LISTENER_INL
#define EVENT_LISTENER_INL

#include "EventManager.h"

template<typename T>
EventListener<T>::~EventListener() {
  EventManager::Instance().RemoveListener(this);
}

template<typename T>
void EventListener<T>::RegisterListener() {
  EventManager::Instance().AddListener(this);
}

template<typename T>
void EventListener<T>::HandleEvent(const Event& event) {
  if (auto* specificEvent = dynamic_cast<const T*>(&event)) {
    OnEvent(*specificEvent);
  }
}

#endif