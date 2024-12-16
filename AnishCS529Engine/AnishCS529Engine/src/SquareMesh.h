/*!****************************************************************************
 * \file   SquareMesh.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-15-2024
 * \brief  Square Mesh class to create a square mesh without user input
 * 
 *****************************************************************************/
#ifndef SQUAREMESH_H
#define SQUAREMESH_H

#pragma once

#include "Mesh.h"

class SquareMesh : public Mesh {
public:
  SquareMesh();
  ~SquareMesh() = default;
};

#endif
