#include "precompiled.h"
#include "EngineMath.h"

 float EngineMath::clamp(float value, float min, float max)
 {
   return (value < min) ? min : ((value > max) ? max : value);
 }
