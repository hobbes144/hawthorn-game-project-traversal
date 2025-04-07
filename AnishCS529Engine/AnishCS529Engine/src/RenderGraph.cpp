#include "precompiled.h"
#include "RenderGraph.h"

/*!****************************************************************************
 * \brief Initialize the RenderGraph
 * 
 * This is used to initialzie the EBOs for the camera and the lights to reduce
 * uniform updates for each render pass.
 * 
 *****************************************************************************/
void RenderGraph::initialize()
{
  initializeLightUBOs();
  initializeCameraUBO();
}

void RenderGraph::draw(SceneGraph* scene)
{
  for (const auto& camera : scene->getCameras()) {

    updateCameraUBO(camera);
    updateLightUBOs(scene->getLights());

    for (const auto& pass : renderStack) {
      pass->draw(camera, scene);
    }

  }
}

/*!****************************************************************************
 * \brief Initialize the Lights UBO
 * 
 * This sets up the UBO for the SunLight and AmbientLight specifically.
 * This allows us to set up the lights only once at the start of the draw loop
 * and then reuse it in all the render passes.
 * 
 * Any shader that has the UBO binding 1 set to "lights" will use these values.
 * 
 *****************************************************************************/
void RenderGraph::initializeLightUBOs()
{
  glGenBuffers(1, &uboLights);
  glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
  glBufferData(
    GL_UNIFORM_BUFFER,
    sizeof(DirectionalLight) + sizeof(AmbientLight),
    NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(
    GL_UNIFORM_BUFFER, 1, uboLights, 0, 
    sizeof(DirectionalLight) + sizeof(AmbientLight));
}

/*!****************************************************************************
 * \brief Initialize the Camera UBO
 * 
 * This sets up the UBO for the camera's viewProjectionMatrix specifically.
 * This allows us to set up the camera only once at the start of the draw loop
 * and then reuse it in all the render passes.
 * 
 * Any shader that has the UBO binding 0 set to "camera" will use these values.
 * 
 *****************************************************************************/
void RenderGraph::initializeCameraUBO()
{
  glGenBuffers(1, &uboCamera);
  glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(Matrix4) * 2 + sizeof(float), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboCamera, 0, sizeof(Matrix4) * 2);
}

void RenderGraph::updateLightUBOs(Lights lights)
{
  glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
  glBufferSubData(GL_UNIFORM_BUFFER,
    0, sizeof(DirectionalLight),
    &(lights.sunLight));
  glBufferSubData(GL_UNIFORM_BUFFER,
    sizeof(DirectionalLight), sizeof(AmbientLight),
    &(lights.ambientLight));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void RenderGraph::updateCameraUBO(std::shared_ptr<Camera> camera)
{
  glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
  glBufferSubData(GL_UNIFORM_BUFFER,
    0, sizeof(Matrix4),
    camera->getViewProjectionMatrix().getData());
  glBufferSubData(GL_UNIFORM_BUFFER,
    sizeof(Matrix4), sizeof(Matrix4),
    camera->getInverseViewMatrix().getData());
  glBufferSubData(GL_UNIFORM_BUFFER,
    sizeof(Matrix4) * 2, sizeof(float),
    &(camera->getExposure()));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
