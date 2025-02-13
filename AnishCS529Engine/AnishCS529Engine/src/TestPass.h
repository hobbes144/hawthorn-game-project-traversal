/*!****************************************************************************
 * \file   TestPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-12-2025
 * \brief  Test RenderPass for the Engine Demo
 * 
 *****************************************************************************/
#ifndef TEST_PASS_H
#define TEST_PASS_H

#pragma once

#include "RenderPass.h"

class TestPass : public RenderPass {
public:
  TestPass() : RenderPass() {
    this->addShader("shaders/lighting.vert\nshaders/lighting.frag");
  };
};

#endif // !TEST_PASS_H
