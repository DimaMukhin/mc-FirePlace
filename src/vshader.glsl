#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() 
{
  gl_Position = projection * view * model * vPosition;
  color = vColor;
} 
