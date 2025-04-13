#include "precompiled.h"
#include "EngineMath.h"

namespace EngineMath {

  float clamp(float value, float min, float max)
  {
    return (value < min) ? min : ((value > max) ? max : value);
  }

// Random
  namespace Random {
    float boundedFloat(float min, float max)
    {
      static std::mt19937 gen([] {
        std::random_device rd;
        return std::mt19937(rd());
      }());

      std::uniform_real_distribution<float> dist(min, max);
      return dist(gen);
    }
  }

}
