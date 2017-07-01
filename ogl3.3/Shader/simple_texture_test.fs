#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;   

uniform sampler2D ourTexture;

void main(){
    //FragColor = texture(ourTexture, TexCoord);
    //我们还可以把得到的纹理颜色与顶点颜色混合，来获得更有趣的效果。
    //我们只需把纹理颜色与顶点颜色在片段着色器中相乘来混合二者的颜色：
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}