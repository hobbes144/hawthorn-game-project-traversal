/*!****************************************************************************
 * \file   DebugMaterial.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * 
 *****************************************************************************/
#include "DebugMaterial.h"

void DebugMaterial::draw(std::shared_ptr<Mesh> mesh) const
{
  renderGraph->draw(mesh, properties, GL_LINES);
}
