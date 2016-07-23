#version 330

layout (location = 0) in vec3 Position;
uniform float u_scale;

void main()
{
    gl_Position = vec4(u_scale * Position.x, u_scale * Position.y, Position.z, 1.0);
}