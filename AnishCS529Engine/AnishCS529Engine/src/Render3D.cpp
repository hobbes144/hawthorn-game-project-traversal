/*!****************************************************************************
 * \file   Render3D.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-15-2024
 *
 *****************************************************************************/
#include "precompiled.h"
#include "Render3D.h"
#include "GameObject.h"


 /*!****************************************************************************
  * \brief Set the mesh to be rendered
  *
  * ## Usage:
  *
  * This sets the mesh to be rendered.
  *
  * ## Explanation:
  *
  * The update() call will draw the mesh to the screen using the material.
  *
  * \param _mesh Mesh to be rendered
  * \return \b std::shared_ptr<Render3D> Self shared pointer to allow chaining.
  *****************************************************************************/
std::shared_ptr<Render3D> Render3D::setMesh(std::shared_ptr<Mesh> _mesh)
{
  mesh = _mesh;
  return shared_from_this();
}


/*!****************************************************************************
 * \brief Set the mesh to be rendered
 *
 * ## Usage:
 *
 * This sets the mesh to be rendered.
 *
 * ## Explanation:
 *
 * The update() call will draw the mesh to the screen using the material.
 *
 * \param _material Material to be rendered
 * \return \b std::shared_ptr<Render3D> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<Render3D> Render3D::setMaterial(std::shared_ptr<Material> _material)
{
  material = _material;
  renderMask = _material->getDefaultRenderMask();
  return shared_from_this();
}

std::shared_ptr<Render3D> Render3D::setDrawMode(GLenum _drawMode) {
  drawMode = _drawMode;
  return shared_from_this();
}

/*!****************************************************************************
 * \brief Dummy initialize function
 *
 *****************************************************************************/
void Render3D::initialize() {}

/*!****************************************************************************
 * \brief Dummy update function
 *
 * \param deltaTime Dummy deltaTime
 *****************************************************************************/
void Render3D::update(float deltaTime)
{}

/*!****************************************************************************
 * \brief Dummy shutdown function
 *
 *****************************************************************************/
void Render3D::shutdown() {}

/*!****************************************************************************
 * \brief Draw objects to screen
 *
 * ## Usage:
 *
 * This call should be made when the object must be drawn to the GameWindow.
 *
 * ## Explanation:
 *
 * This call sets up the Renderer to use the Material and Mesh to draw to the
 * GameWindow
 *
 *****************************************************************************/
void Render3D::draw(std::shared_ptr<Shader> shader) {
  if (!enabled) return;

  material->setProperty("ModelMatrix", parent->getTransformMatrix());
  material->setProperty("InvModelMatrix", parent->getTransform().getInverseLocalMatrix());

  for (const auto& property : properties) {
    material->setTempProperty(property.first, property.second);
  }

  material->apply(shader);

  if (shader->getDrawMode())
    mesh->draw(shader->getDrawMode());
  else
    mesh->draw(drawMode);
}


