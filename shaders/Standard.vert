#version 450 core


// Uniforms
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;


// Stage inputs
layout (location = 0) in vec3 i_vertex;


// Main
void main(void)
{
  gl_Position = u_projectionMatrix * u_viewMatrix * vec4(i_vertex, 1.0);
}
