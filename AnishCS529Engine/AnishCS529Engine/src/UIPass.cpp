#include "precompiled.h"
#include "UIPass.h"

UIPass::UIPass() : RenderPass() {
  this->addShader("shaders/ui.vert\nshaders/ui.frag");

  renderMask = RenderMask::UIPass;
}
