#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 orthographicMatrix;
void main()
{
//    gl_Position = vec4(aPos, 1.0);
//    gl_Position = orthographicMatrix * modelMatrix * 
  vec4(aPos, 1.0);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * 
  vec4(aPos, 1.0);
  ourColor = aColor;
}