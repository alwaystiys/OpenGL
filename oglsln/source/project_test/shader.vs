#version 330

layout (location = 0) in vec3 Position;
uniform float u_scale;
uniform mat4 u_world;
out vec4 color;

void main()
{
    gl_Position = u_world * vec4(Position, 1.0);
	color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}