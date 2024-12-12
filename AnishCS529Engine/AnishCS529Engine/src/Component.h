/*!****************************************************************************
 * \file   Component.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-10-2024
 * \brief  Component Class used as the base of the Entity Component System.
 * 
 *****************************************************************************/
#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include "Node.h"

#include <string>

/*!****************************************************************************
 * \brief Component is the base class of all components.
 * 
 * Component is a pure virtual class that is to be derived for each component.
 * 
 * The components must implement the following functionality:
 * - initialize()
 * - update(float deltaTime)
 * - shutdown()
 * 
 * Constructor and destructor of child classes must be default.
 * 
 * Components may have an enabled or disabled state. Default constructor sets
 * component as enabled. This may be changed after construction.
 * 
 * Components can be marked for deletion, in which case the object should not
 * be used again. Default constructor sets component as not marked for
 * deletion.
 * 
 *****************************************************************************/
class Component {
public:
  Component() : enabled(true), markedForDeletion(false) {}
  virtual ~Component();
  virtual void initialize();
  virtual void update(float deltaTime);
  virtual void shutdown();

  void enable();
  void disable();
  bool isEnabled();

  void markForDeletion();
  bool isMarkedForDeletion();

protected:
  bool enabled;
  bool markedForDeletion;
};

#endif
