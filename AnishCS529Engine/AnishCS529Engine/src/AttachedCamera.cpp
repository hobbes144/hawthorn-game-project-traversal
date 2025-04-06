#include "precompiled.h"
#include "AttachedCamera.h"


/* Private functions */

/*!****************************************************************************
 * \brief Update the view matrix based on the location of the camera
 *
 * ## Explanation:
 *
 * The view matrix is always calculated as the same rotation of the camera, but
 * with the negative of the position of the camera. This ensures that all
 * objects in front of the camera are moved to the relative position from the
 * world origin.
 *
 *****************************************************************************/
void AttachedCamera::updateViewMatrix() {
  if (position != attachedNode->getWorldTransform().getPosition() || rotation != attachedNode->getWorldTransform().getRotation()) {
    position = attachedNode->getWorldTransform().getPosition();
    rotation = attachedNode->getWorldTransform().getRotation();

    // Extract basis vectors (Right, Up, Forward)
    forward = rotation.forward();
    up = rotation.up();
    right = rotation.right();

    // Compute view matrix using LookAt
    viewMatrix = Matrix4::lookAt(position, position + forward, up);
    inverseViewMatrix = Matrix4::inverse(viewMatrix);
  }
}

std::shared_ptr<AttachedCamera> AttachedCamera::attachToNode(std::shared_ptr<Node> node) {
  attachedNode = node;

  return shared_from_this();
}
