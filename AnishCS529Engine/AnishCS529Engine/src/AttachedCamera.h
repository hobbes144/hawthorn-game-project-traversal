/*!****************************************************************************
 * \file   AttachedCamera.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-01-2025
 * \brief  Camera attached to a GameObject
 * 
 *****************************************************************************/
#ifndef ATTACHED_CAMERA_H
#define ATTACHED_CAMERA_H

#pragma once

#include <cassert>

 /* Base class */
#include "Camera.h"
#include "Node.h"

class AttachedCamera : public Camera, public std::enable_shared_from_this<AttachedCamera> {
public:
  AttachedCamera(std::string _name) : Camera(_name) {};
  ~AttachedCamera() = default;

  /* Component functions */
  virtual void update();

  std::shared_ptr<AttachedCamera> attachToNode(std::shared_ptr<Node> node);

private:
  std::shared_ptr<Node> attachedNode;

  void updateViewMatrix();
};

#endif // !ATTACHED_CAMERA_H
