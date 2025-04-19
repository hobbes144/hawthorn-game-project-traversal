/*!****************************************************************************
 * \file   AttachedCamera.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-01-2025
 * \brief  Camera attached to a GameObject
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
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

  std::shared_ptr<AttachedCamera> attachToNode(std::shared_ptr<Node> node);

private:
  std::shared_ptr<Node> attachedNode;

  virtual void updateViewMatrix() override;
};

#endif // !ATTACHED_CAMERA_H
