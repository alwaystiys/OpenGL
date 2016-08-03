#version 330

in vec4 color;
out vec4 FragColor;
in vec2 TexCoord0;
uniform sampler2D u_sampler;

void main()
{
     //FragColor = color;
     FragColor = texture2D(u_sampler, TexCoord0.xy); 
}
