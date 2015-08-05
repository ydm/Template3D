#version 450 core

// Stage inputs
// layout (location = 0) in vec3 i_color;

// Stage outputs
layout (location = 0 ) out vec4 o_color;

// Main
void main(void)
{
  o_color = vec4(0.0, 1.0, 0.0, 1.0);
}
