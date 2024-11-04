/*!****************************************************************************
 * \file   Event.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   11-04-2024
 * \brief  Event class that stores specific event actions that get triggered
 * 
 *****************************************************************************/
#ifndef EVENT_H
#define EVENT_H

#pragma once

/*!****************************************************************************
 * \brief Class Event that is inherited from for all event types.
 *****************************************************************************/
class Event {
public:
  /** Default destructor enforced to ensure there are no memory leaks. */
  virtual ~Event() = default;
};

#endif // EVENT_H
