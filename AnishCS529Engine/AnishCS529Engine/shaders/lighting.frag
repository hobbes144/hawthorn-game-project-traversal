/////////////////////////////////////////////////////////////////////////
// Pixel shader for lighting
////////////////////////////////////////////////////////////////////////
#version 440

#define M_PI 3.1415926535897932384626433832795

const float pi = 3.14159265358979323846;

in vec3 normalVec, lightVec, eyeVec;
in vec2 texCoord;
in vec3 tanVec;

layout (binding = 0) uniform camera
{
    mat4 projection;
    mat4 view;
    mat4 inverseView;
    float exposure;
};

struct DirectionalLight {
  vec3 direction;
  float intensity;
  vec3 color;
  float padding0;
};

struct AmbientLight {
  vec3 color;
  float intensity;
};

layout (binding = 1) uniform lights
{
  DirectionalLight sunLight;
  AmbientLight ambientLight;
};

uniform vec3 diffuse;   // Kd
uniform vec3 specular;  // Ks
uniform float shininess; // alpha exponent

uniform bool useTexture;
uniform sampler2D mainTexture;
uniform vec2 mainTextureScale;

uniform bool useNormalMap;
uniform sampler2D normalMap;
uniform vec2 normalMapScale;

uniform bool HDR;

out vec3 FragColor;

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

void main()
{
    vec2 uv;

//    uv = gl_FragCoord.xy/vec2(750,750); // (or whatever screen size)
//    FragColor = 10.0*vec3(texture(irrandianceMap, uv)); // or similar
//    return FragColor; // which disables all further code in the shader.
//

    vec3 N = normalize(normalVec);
    vec3 L = -normalize(lightVec);
    vec3 V = normalize(eyeVec);

    vec3 Kd = diffuse;
    vec3 Ii = sunLight.color * sunLight.intensity;
    vec3 Ks = specular;
    float alpha = shininess;

    vec3 Ia = ambientLight.color * ambientLight.intensity;


    // Texture mapping ...
    // This section only calculates the Kd and modified uv for some objects.
    // The modified uv ignores scaling, this is just to modify how textures
    // are handled in general, such as flipping.
    uv = texCoord;

    vec2 scaledTexCoord = uv * mainTextureScale;
      
    vec4 color = texture(mainTexture, scaledTexCoord);
    Kd = color.rgb;

    // The normal map calc ...
    if (useNormalMap) {
      vec2 scaledTexCoord = uv * normalMapScale;
      vec3 delta = texture(normalMap, scaledTexCoord).xyz;
      delta = delta*2.0 - vec3(1.0);
      vec3 T = normalize(tanVec);
      vec3 B = normalize(cross(T,N));
      N = delta.x*T + delta.y*B + delta.z*N;
    }

    if (HDR) {
      Kd = toLinear(Kd);
    }
    
    // The lighting calculation ...
    vec3 H = normalize(L+V);
    float LN = max(dot(L,N),0.0);
    float HN = max(dot(H,N),0.0);
    float VN = max(dot(V,N),0.0);
    float LH = max(dot(L,H),0.0);

    vec3 ambientDiffuse = Ia*Kd;

    // BRDF
    vec3 F = Ks + (((1,1,1)-Ks)*pow((1-LH),5.0));
    float D = ((alpha+2.0)/(2*M_PI))*(pow(HN,alpha));
    vec3 BRDF = (Kd/M_PI) + ((F*D)/(4*pow(max(LH,0.0000000001),2.0)));
    FragColor = ambientDiffuse + (Ii*LN*BRDF);

    if (HDR) {
      FragColor = toSRGB(FragColor);
    }
}
