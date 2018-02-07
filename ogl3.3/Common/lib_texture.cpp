#include "Common/lib_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Common/stb_image.h"

Texture::Texture(const char* fileName, GLenum format) {
    this->m_fileName = fileName;
	// useless field
    this->m_format = format;
}

Texture::~Texture() {
}

bool Texture::Load() {
    glGenTextures(1, &m_textureObj);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
    // wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLint width, height, nrChannels;
    unsigned char *data = stbi_load(this->m_fileName, &width, &height, &nrChannels, 0);
    if(data) {
		GLenum format;
		if(nrChannels == 1)
			format = GL_RED;
		else if(nrChannels == 3)
			format = GL_RGB;
		else if(nrChannels == 4)
			format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        return false;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void Texture::Bind(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
}

void Texture::setLoadFlipVertically() {
    stbi_set_flip_vertically_on_load(true);
}