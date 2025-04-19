/*!****************************************************************************
 * \file   EventListener.inl
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * \brief  EventListener template implementations (after EventManager
 * definition)
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
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