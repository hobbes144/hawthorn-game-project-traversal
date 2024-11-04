/*!****************************************************************************
 * \file   EventListener.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * \brief  Event listener object that contains logic to trigger an event
 * 
 *****************************************************************************/
#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#pragma once

#include "Event.h"

class IEventListener {
public:
  virtual ~IEventListener() = default;
  virtual void handleEvent(const Event& event) = 0;
};

/* Forward declaration of EventManager class so we can use it here. */
class EventManager;

template <typename T>
class EventListener : public IEventListener
{
public:
  EventListener() = default;
  virtual ~EventListener();

  void registerListener();

  virtual void runEventAction(const T& event) = 0;

  void handleEvent(const Event& event) override;
};

#include"EventListener.inl"

#endif // !EVENT_LISTENER_H
