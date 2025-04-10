#include "precompiled.h"
#include "FBO.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include "fbo.h"

void FBO::createFBO(const int w, const int h) {
  width = w;
  height = h;

  glGenFramebuffersEXT(1, &fboID);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboID);

  // Create a render buffer, and attach it to FBO's depth attachment
  unsigned int depthBuffer;
  glGenRenderbuffersEXT(1, &depthBuffer);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT,
    width, height);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
    GL_RENDERBUFFER_EXT, depthBuffer);

  // Check for completeness/correctness
  int status = (int)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
  if ( status != int(GL_FRAMEBUFFER_COMPLETE_EXT) )
    printf("FBO Error: %d\n", status);

  // Unbind the fbo until it's ready to be used
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO::setViewport(const int w, const int h) {}

void FBO::attachTexture(TextureManager::TextureID textureID) {

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboID);

  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
    GL_TEXTURE_2D, textureID, 0);

  // Check for completeness/correctness
  int status = (int)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
  if ( status != int(GL_FRAMEBUFFER_COMPLETE_EXT) )
    printf("FBO Error: %d\n", status);

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO::bindFBO() { glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboID); }
void FBO::unbindFBO() { glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); }
