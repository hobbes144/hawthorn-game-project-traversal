/////////////////////////////////////////////////////////////////////////
// Pixel shader for lighting
////////////////////////////////////////////////////////////////////////
#version 430

#define M_PI 3.1415926535897932384626433832795

const float pi = 3.14159265358979323846;

in vec3 eyeVec;
uniform sampler2D texture0;
uniform vec2 texScale0;
uniform sampler2D texture1;
uniform vec2 texScale1;

// Shadow Map
uniform bool enableShadows;
uniform sampler2D shadowMap;
in vec4 shadowCoord;

// Reflection Map
uniform bool enableReflections;
uniform sampler2D topReflectionMap;
uniform sampler2D bottomReflectionMap;

// Irradiance Map
uniform bool enableIrradiance;
uniform sampler2D irrandianceMap;

uniform bool enableExposure;
uniform float exposure;

vec3 toLinear(vec3 color) {
  return pow(
      (
        (exposure * color) / 
        (
          (exposure * color) + 
          vec3(1.0)
        )
      ), vec3(2.2));
}

vec3 toSRGB(vec3 color) {
  return pow(
      (
        (exposure * color) / 
        (
          (exposure * color) + 
          vec3(1.0)
        )
      ), vec3(1/2.2));
}

vec3 LightingFragment()
{
    vec3 FragColor;

    vec3 V = normalize(eyeVec);
    
    // Sky skips light processing so using a shortcut.
    vec3 uv = vec2(atan(V.x,V.z)/(2.0f*pi), acos(V.y)/pi);
    vec4 color = texture(texture0, uv);
    FragColor = color.rgb;
    if (HDR) {
      FragColor = toSRGB(FragColor);
    }
    return FragColor;
}
