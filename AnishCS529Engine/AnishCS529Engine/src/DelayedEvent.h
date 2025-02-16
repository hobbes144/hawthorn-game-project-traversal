/*!****************************************************************************
 * \file   DelayedEvent.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-15-2025
 * \brief  Delayed Event used to handle events that need to occur at specific
 * timestamps
 * 
 *****************************************************************************/
#ifndef DELAYED_EVENT_H
#define DELAYED_EVENT_H

#pragma once

#include <functional>

#include "Event.h"

 /*!****************************************************************************
  * \brief Class Event that is inherited from for all event types.
  *****************************************************************************/
class DelayedEvent : public Event{
public:
  using DelayedEventCallback = std::function<void()>;
  DelayedEvent(float _execTime, DelayedEventCallback _callback) : 
    execTime(_execTime), callback(std::move(_callback)) {}

  bool operator>(const DelayedEvent& other) const {
    return execTime > other.execTime;
  }

  float execTime;
  DelayedEventCallback callback;
};

#endif // DELAYED_EVENT_H
