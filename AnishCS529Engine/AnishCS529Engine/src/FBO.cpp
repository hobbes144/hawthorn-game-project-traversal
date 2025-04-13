/*!****************************************************************************
 * \file   FBO.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-09-2025
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "FBO.h"

void FBO::initialize() {
  glGenFramebuffers(1, &fboID);
  glBindFramebuffer(GL_FRAMEBUFFER, fboID);

  // Create a render buffer, and attach it to FBO's depth attachment
  unsigned int depthBuffer;
  glGenRenderbuffers(1, &depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
    width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    GL_RENDERBUFFER, depthBuffer);

  // Check for completeness/correctness
  int status = (int)glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if ( status != int(GL_FRAMEBUFFER_COMPLETE) )
    printf("FBO Error: %d\n", status);

  // Unbind the fbo until it's ready to be used
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::finalize() {
  glBindFramebuffer(GL_FRAMEBUFFER, fboID);

  std::vector<GLenum> attachments;
  for (int i = 0; i <= attachedTextures; i++) {
    attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
  }
  glDrawBuffers(attachments.size(), attachments.data());

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "FBO not complete!" << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0); // done
}

void FBO::setViewport(const int w, const int h) {
  width = w;
  height = h;
}

void FBO::attachTexture(TextureManager::TextureID textureID) {

  glBindFramebuffer(GL_FRAMEBUFFER, fboID);
  glFramebufferTexture2D(
    GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachedTextures,
    GL_TEXTURE_2D, textureID, 0);

  /*std::cout << "Bound texture to FBO: " << textureID << " at " << GL_COLOR_ATTACHMENT0 + attachedTextures << std::endl;
  std::string label = "FBO_" + std::to_string(fboID) + "_" + std::to_string(attachedTextures);
  glObjectLabel(GL_TEXTURE, textureID, -1, label.c_str());*/

  // Check for completeness/correctness
  int status = (int)glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != int(GL_FRAMEBUFFER_COMPLETE))
    printf("FBO Error: %d\n", status);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  attachedTextures++;
}

void FBO::bind() { glBindFramebuffer(GL_FRAMEBUFFER, fboID); }
void FBO::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
