/*!****************************************************************************
 * \file   RenderableNode.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "RenderableNode.h"

void RenderableNode::update(float deltaTime) {
  /* Todo: figure out logic here. Maybe a callback to a behaviour controller?*/

  Node::update(deltaTime);
}

void RenderableNode::draw(const Matrix4& view, const Matrix4& projection) {
  if (!isVisible)
    return;

  material->setProperty("ViewMatrix", view);
  material->setProperty("ProjectionMatrix", projection);
  material->setProperty("ModelMatrix", getTransformMatrix());

  // Todo: decide what to do with RenderableNode. We might want to delete it
  // entirely. Or rework to work with the new sceneGraph and render system.
  //material->draw(mesh);

  for (auto& child : getChildren()) {
    /* This line will return null if child is of type Node, and return the
       child if it is of type RenderableNode
    */
    if (auto renderableChild = 
      std::dynamic_pointer_cast<RenderableNode>(child)) {
      renderableChild->draw(view, projection);
    }
  }

}
