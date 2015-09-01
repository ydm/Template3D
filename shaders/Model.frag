#version 450 core

// Stage inputs
layout (location = 0) in vec3 i_normal;

// Stage outputs
layout (location = 0 ) out vec3 o_color;

// Main
void main(void)
{
  o_color = normalize(i_normal);
}
