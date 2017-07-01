#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;   

uniform sampler2D ourTexture;

void main(){
    //FragColor = texture(ourTexture, TexCoord);
    //���ǻ����԰ѵõ���������ɫ�붥����ɫ��ϣ�����ø���Ȥ��Ч����
    //����ֻ���������ɫ�붥����ɫ��Ƭ����ɫ�����������϶��ߵ���ɫ��
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}