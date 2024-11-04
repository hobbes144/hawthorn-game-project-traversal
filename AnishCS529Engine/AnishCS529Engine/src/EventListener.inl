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
#ifndef EVENT_LISTENER_INL
#define EVENT_LISTENER_INL

#include "EventManager.h"

template <typename T>
EventListener<T>::~EventListener() {
  EventManager::Instance().removeListener(this);
}

template <typename T>
void EventListener<T>::registerListener() {
  EventManager::Instance().addListener(this);
}

template <typename T>
void EventListener<T>::handleEvent(const Event& event) {
  if (auto* specificEvent = dynamic_cast<const T*>(&event)) {
    runEventAction(*specificEvent);
  }
}

#endif // EVENT_LISTENER_INL
