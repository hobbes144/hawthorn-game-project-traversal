/*!****************************************************************************
 * \file   RendererStateSaver.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-08-2025
 * 
 *****************************************************************************/

#include "RendererStateSaver.h"

 /* StateSaver Class */
 /*!****************************************************************************
  * \brief Constructor for StateSaver
  *
  * ## Explanation:
  *
  * This will save the state of the renderer when created.
  *
  * \param renderer
  *****************************************************************************/
Renderer::StateSaver::StateSaver(Renderer& renderer) :
  savedRenderer(renderer), savedState(renderer.getCurrentState()) {};

/*!****************************************************************************
 * \brief Destructor for StateSaver
 *
 * ## Explanation:
 *
 * This will restore the state of the renderer to the state it was in when
 * this object was created.
 *
 *****************************************************************************/
Renderer::StateSaver::~StateSaver() {
  savedRenderer.setState(savedState);
}
