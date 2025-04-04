/////////////////////////////////////////////////////////////////////////
// Pixel shader for lighting
////////////////////////////////////////////////////////////////////////
#version 430

#define M_PI 3.1415926535897932384626433832795

//out vec4 FragColor;

// These definitions agree with the ObjectIds enum in scene.h
const int     nullId	= 0;
const int     skyId	= 1;
const int     seaId	= 2;
const int     groundId	= 3;
const int     roomId	= 4;
const int     boxId	= 5;
const int     frameId	= 6;
const int     lPicId	= 7;
const int     rPicId	= 8;
const int     teapotId	= 9;
const int     spheresId	= 10;
const int     floorId	= 11;

const float pi = 3.14159265358979323846;

in vec3 normalVec, lightVec, eyeVec;
in vec2 texCoord;
in vec3 tanVec;

uniform int objectId;
uniform int mode;
uniform int textureMode;
uniform vec3 diffuse;   // Kd
uniform vec3 specular;  // Ks
uniform float shininess; // alpha exponent

uniform vec3 Light;     // Ii
uniform vec3 Ambient;   // Ia

uniform int numTextures;
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
    vec2 uv;
    vec3 FragColor;

//    uv = gl_FragCoord.xy/vec2(750,750); // (or whatever screen size)
//    FragColor = 10.0*vec3(texture(irrandianceMap, uv)); // or similar
//    return FragColor; // which disables all further code in the shader.
//

    vec3 N = normalize(normalVec);
    vec3 L = normalize(lightVec);
    vec3 V = normalize(eyeVec);

    vec3 Kd = diffuse;   
    vec3 Ii = Light;
    vec3 Ks = specular;
    float alpha = shininess;

    vec3 Ia = Ambient;


    // Texture mapping ...
    // This section only calculates the Kd and modified uv for some objects.
    // The modified uv ignores scaling, this is just to modify how textures
    // are handled in general, such as flipping.
    if (textureMode == 1) {
      if (objectId == rPicId) {
        uv = texCoord;

        vec2 scaledTexCoord = uv * texScale0;

        scaledTexCoord = (scaledTexCoord - 0.1f) / 0.8f;

        if ( texCoord.x <= 0.1f || texCoord.x >= 0.9f || texCoord.y <= 0.1f || texCoord.y >= 0.9f ) {
          Kd = vec3(0.5f);
        }
        else {
          vec4 color = texture(texture0, scaledTexCoord);
          Kd = color.rgb;
        }
      }
      else if (objectId == lPicId) {
        uv = vec2(texCoord.x - 0.5f, texCoord.y);

        float theta = (atan(uv.y, uv.x) * 2.0f / pi);
        float red_val = mod(length(uv), ((1.0f+theta)*0.05f))*5.0f;
        Kd = vec3(
          max(
            red_val,
            sin(smoothstep(0.0, 1.0,pow(red_val*pi/2.0f, 5.0)))
          ), // red
          sin(smoothstep(0.0, 1.0,pow(red_val*pi/2.0f, 5.0))), // green
          sin(smoothstep(0.0, 1.0,pow(red_val*pi/2.0f, 5.0)))  // blue
        );
      }
      else if (objectId == skyId) {
        // Sky skips light processing so using a shortcut.
        uv = vec2(atan(V.x,V.z)/(2.0f*pi), acos(V.y)/pi);
        vec4 color = texture(texture0, uv);
        FragColor = color.rgb;
        if (enableExposure) {
          FragColor = toSRGB(FragColor);
        }
        return FragColor;
      }
      else if (objectId == seaId) {
        uv = texCoord;
      }// Calc done at end to avoid lighting.
      else {
        if ( objectId == roomId )
          uv = texCoord.yx;
        else
          uv = texCoord;

        vec2 scaledTexCoord = uv * texScale0;
      
        vec4 color = texture(texture0, scaledTexCoord);
        Kd = color.rgb;
      }
    }
    else {
        uv = vec2(floor(100.0*texCoord));
        // A checkerboard pattern to break up large flat expanses.  Remove when using textures.
        if (objectId==groundId || objectId==floorId || objectId==seaId) {
            ivec2 uvI = ivec2(floor(100.0*texCoord));
            if ((uvI[0]+uvI[1])%2==0)
                Kd *= 0.9; 
        }
    }

    // The normal map calc ...
    if (textureMode == 1 && numTextures > 1 ) {
      vec2 scaledTexCoord = uv * texScale1;
      vec3 delta = texture(texture1, scaledTexCoord).xyz;
      delta = delta*2.0 - vec3(1.0);
      vec3 T = normalize(tanVec);
      vec3 B = normalize(cross(T,N));
      N = delta.x*T + delta.y*B + delta.z*N;
    }

    if (textureMode == 1 && enableExposure) {
      Kd = toLinear(Kd);
    }

    // The shadow calculation
    bool inShadow = false;
    if (enableShadows) {
      vec2 shadowIndex = shadowCoord.xy/shadowCoord.w;
      if (shadowCoord.w > 0 && 
        shadowIndex.x >= 0.0f && shadowIndex.x < 1.0f &&
        shadowIndex.y >= 0.0f && shadowIndex.y < 1.0f){
          float lightDepth = texture(shadowMap, shadowIndex).w;
          float pixelDepth = shadowCoord.w;
          if ( pixelDepth > (lightDepth + 0.01f) )
            inShadow = true;
      }
    }
    
    // The lighting calculation ...
    vec3 H = normalize(L+V);
    float LN = max(dot(L,N),0.0);
    float HN = max(dot(H,N),0.0);
    float VN = max(dot(V,N),0.0);
    float LH = max(dot(L,H),0.0);

    if (mode == -1) {
      FragColor = Kd;
      return FragColor;
    }

    if (mode == 0) {
      FragColor = vec3(0.5,0.5,0.5)*Kd + Kd*max(dot(L,N),0.0);
      return FragColor;
    }

    if (mode == 1) {
      // Phong
      FragColor = (Ia*Kd) + (Ii*Kd*LN) + (Ii*Ks*pow(HN,alpha));
      return FragColor;
    }
    

    // Special processing for Sea reflection
    if (textureMode == 1 && objectId == seaId) {
      vec3 R = -(2.0*(max(dot(V,N),0.0))*N - V);
      uv = vec2(-atan(R.y,R.x)/(2*pi), acos(R.z)/pi);
      vec4 color = texture(texture0, uv);
      if (mode == 2 && !inShadow) {
        // BRDF specifically for sea
        vec3 F = Ks + (((1,1,1)-Ks)*pow((1-LH),5.0));
        float D = ((alpha+2.0)/(2*M_PI))*(pow(HN,alpha));
        vec3 BRDF = (color.xyz/M_PI) + ((F*D)/(4*pow(max(LH,0.0000000001),2.0)));
        color.xyz = color.xyz + 0.1*(Ii*LN*BRDF);
      }
      FragColor = color.rgb;
      return FragColor;
    }

    vec3 ambientDiffuse = Ia*Kd;

    if (enableIrradiance) {
      uv = vec2(-atan(-N.y,-N.x)/(2.0f*pi), acos(N.z)/pi);
      ambientDiffuse = ambientDiffuse + Kd * (50.0*texture(irrandianceMap, uv).xyz) / M_PI;
    }

    if (mode == 2) {
      // BRDF
      vec3 F = Ks + (((1,1,1)-Ks)*pow((1-LH),5.0));
      float D = ((alpha+2.0)/(2*M_PI))*(pow(HN,alpha));
      vec3 BRDF = (Kd/M_PI) + ((F*D)/(4*pow(max(LH,0.0000000001),2.0)));
      if (inShadow) {
        FragColor = ambientDiffuse;
      }
      else {
        FragColor = ambientDiffuse + (Ii*LN*BRDF);
      }
    }

    // Teapot reflections
    if (enableReflections) {
      float scaling = 0.2;
      if (objectId == teapotId)
        scaling = 0.2;
      else if(objectId == boxId)
        scaling = 0.005;
      else if(objectId == floorId)
        scaling == 0.1;
        
      vec3 R = normalize(2*(VN)*N - V);

      if (R.z > 0) {
        uv = (vec2(R.x,R.y)/(1+R.z)) * 0.5 + vec2(0.5);
        FragColor = FragColor*(1-scaling) + scaling*texture(topReflectionMap, uv).xyz;
      }
      else {
        uv = (vec2(R.x,R.y)/(1-R.z)) * 0.5 + vec2(0.5);
        FragColor = FragColor*(1-scaling) + scaling*texture(bottomReflectionMap, uv).xyz;
      }
    }

    if (enableExposure) {
      FragColor = toSRGB(FragColor);
    }
    return FragColor;
}
