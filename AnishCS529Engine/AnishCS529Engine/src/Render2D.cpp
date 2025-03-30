/*!****************************************************************************
 * \file   Render2D.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-15-2024
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "Render2D.h"

/*!****************************************************************************
 * \brief Set the camera to be rendered to
 * 
 * ## Usage:
 * 
 * The sets up which camera to use for rendering. This is needed before any
 * update() calls can be made.
 * 
 * ## Explanation:
 * 
 * The update() call draws the object to the screen, but to do so, the
 * viewMatrix and projectionMatrix are needed. These are set up in the Camera
 * object. When multiple cameras are involved, this helps ensure rendering
 * occurs to the correct region of the screen.
 * 
 * \param _camera Camera object pointer.
 * \return \b std::shared_ptr<Render2D> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<Render2D> Render2D::setCamera(std::shared_ptr<Camera> _camera)
{
  camera = _camera;
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
 * \param _mesh Mesh to be rendered
 * \return \b std::shared_ptr<Render2D> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<Render2D> Render2D::setMesh(std::shared_ptr<Mesh> _mesh)
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
 * \return \b std::shared_ptr<Render2D> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<Render2D> Render2D::setMaterial(std::shared_ptr<Material> _material)
{
  material = _material;
  return shared_from_this();
}

/*!****************************************************************************
 * \brief Dummy initialize function
 * 
 *****************************************************************************/
void Render2D::initialize() {}

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
 * \param deltaTime Dummy deltaTime
 *****************************************************************************/
void Render2D::update(float deltaTime)
{
  if (!enabled) return;

  material->setProperty("ViewMatrix", camera->getViewMatrix());
  material->setProperty("InverseViewMatrix", camera->getInverseViewMatrix());
  material->setProperty("ProjectionMatrix", camera->getProjectionMatrix());
  material->setProperty("ModelMatrix", parent->getTransformMatrix());
  material->setProperty("InvModelMatrix", parent->getTransform().getInverseLocalMatrix());

  for (const auto& property : properties) {
    material->setTempProperty(property.first, property.second);
  }

  material->draw(mesh);

  material->clearTempProperties();
}

/*!****************************************************************************
 * \brief Dummy shutdown function
 * 
 *****************************************************************************/
void Render2D::shutdown() {}


