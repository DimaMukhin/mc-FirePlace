#version 150

flat in vec4 colorIntensity;
out vec4 fColor;

uniform vec4 baseColor;

void main() 
{ 
    fColor = baseColor + colorIntensity;
}
