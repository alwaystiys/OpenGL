#ifndef LIB_TEXTURE_H
#define LIB_TEXTURE_H
#include <GL/glew.h>
#include <iostream>
#include <string>


class Texture {
public:
    Texture(const char* fileName, GLenum m_format);
    ~Texture();
    bool Load();
    void Bind(GLenum textureUnit); //激活纹理单元
    void setLoadFlipVertically();
private:
    const char* m_fileName;
    GLuint m_textureObj;
    GLenum m_format;

};

#endif LIB_TEXTURE_H