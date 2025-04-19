/*!****************************************************************************
 * \file   Component.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    CS529
 * \date   12-10-2024
 * \brief  Component Class used as the base of the Entity Component System.
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include <memory>
#include <string>

class GameObject;

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
 *****************************************************************************/
class Component {
public:
  Component() : enabled(true), markedForDeletion(false) {}
  virtual ~Component() = default;

  /* Component functions */
  virtual void initialize() {};
  virtual void update(float deltaTime) {};
  virtual void shutdown() {};

  /* Utility functions */
  void enable();
  void disable();
  bool isEnabled() const;

  void setParent(std::shared_ptr<GameObject> _parent);
  std::shared_ptr<GameObject> getParent() const;

protected:
  bool enabled;
  bool markedForDeletion;
  std::shared_ptr<GameObject> parent;
};

#endif
