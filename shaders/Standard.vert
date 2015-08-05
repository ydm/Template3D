#version 450 core


// Stage inputs
layout (location = 0) in vec3 i_vertex;


// Main
void main(void)
{
  // gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(i_vertex + s, 1.0);
  gl_Position = vec4(i_vertex + vec3(0.5, 0.5, 0.5), 1.0);
}
