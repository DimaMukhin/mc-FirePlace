#version 150

in  vec4 vPosition;
in  vec4 vColorIntensity;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec4 baseColor;

flat out vec4 colorIntensity;

void main() 
{
  gl_Position = projection * view * model * vPosition;
  colorIntensity = vColorIntensity;
} 
