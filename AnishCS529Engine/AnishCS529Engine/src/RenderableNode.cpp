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
#include "RenderableNode.h"

void RenderableNode::update(float deltaTime) {
  /* Todo: figure out logic here. Maybe a callback to a behaviour controller?*/

  Node::update(deltaTime);
}

void RenderableNode::draw(const Matrix4& view, const Matrix4& projection) {
  if (!isVisible)
    return;

  material->setProperty("viewMatrix", view);
  material->setProperty("projectionMatrix", projection);
  material->setProperty("modelMatrix", worldTransform.getLocalMatrix());//getTransformMatrix());
  material->apply();

  auto geometryBuffer = mesh->getGeometryBuffer();
  geometryBuffer->bind();


  renderer->draw(GL_TRIANGLES, geometryBuffer->getVertexCount());

  geometryBuffer->unbind();

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
