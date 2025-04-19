/*!****************************************************************************
 * \file   GameObject.h
 * \author Anish Murthy (anish.murthy@digipen.edu) (Graphics/Physics functions)
 * \author Nicholas Shaw (nick.shaw@digipen.edu) (Tag Management)
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \date   12-13-2024
 * \brief  Scene Object that represents a renderable object component
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#pragma once

/* Base class */
#include "Node.h"

/* Used classes */
#include "Component.h"
#include "Renderable.h"

/*!****************************************************************************
 * \brief GameObject class that implements a single object in the scene
 * 
 * ## Usage:
 * 
 * GameObjects are the main objects in the game that represent anything from
 * characters to terrain to hidden triggers and so on. GameObjects are meant to
 * be handled by the SceneGraph, and will be called from the
 * SceneGraph::update(float deltaTime) call in the order they exist in the node
 * tree.
 * 
 * ## Pre-initialization calls:
 * 
 * - addComponent(std::shared_ptr<Component> component)
 * 
 * ## General lifecycle of a GameObject:
 * 
 * - Call addComponent() to add the required components. The update function
 * will return the relevant Component once created.
 * - Perform pre-initialization calls for each Component added.
 * - Call update() in the main loop.
 * - If GameObject is no longer needed, call disable() to disable the object.
 * - If garbage collection system is implemented, call markForDeletion() and
 * handle registration to the garbage collection as needed.
 * - Call shutdown at the end of the main loop or in garbage collection system.
 * 
 *****************************************************************************/
class GameObject : public Node {
public:

	enum Tag {
		UNTAGGED,
		PLAYER,
		ENEMY,
		WALL,
		RUNNABLE_WALL,
		CHECKPOINT,
		SYSTEM
	};

  GameObject(std::string name, Tag t = UNTAGGED) : 
    Node(name), tag(t), enabled(true), markedForDeletion(false),
    renderableComponent(nullptr) {};
  ~GameObject();

  Tag getTag() { return tag; }

  /* Component functions */
  virtual void initialize();
  virtual void update(float deltaTime);
  virtual void shutdown();
  virtual void updateComponents(float deltaTime);

  virtual void draw(
    std::shared_ptr<Shader> shader, uint32_t renderMask);

  /* Utility functions */
  template<typename T>
  std::shared_ptr<T> addComponent();
  template<typename T>
  std::shared_ptr<T> addComponent(std::shared_ptr<T> _component);
  template<typename T>
  void removeComponent();
  template<typename T>
  std::shared_ptr<T> findComponent();

  std::shared_ptr<GameObject> enable();
  std::shared_ptr<GameObject> disable();
  bool isEnabled() const;

  /* Lifecycle functions */
  std::shared_ptr<GameObject> markForDeletion();
  bool isMarkedForDeletion() const;
protected:
  /** Vector of components attached to the GameObject */
  std::vector<std::shared_ptr<Component>> components;
  std::shared_ptr<Renderable> renderableComponent;

  /** Is GameObject enabled */
  bool enabled;
  /** Is GameObject marked for deletion */
  bool markedForDeletion;

  /** Tag of the GameObject **/
  Tag tag;

};

#include "GameObject.inl"

#endif // !SCENE_OBJECT_H
