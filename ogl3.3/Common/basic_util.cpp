#include "Common/basic_util.h"

#include <iostream>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#endif
bool ReadFile(const char *pFilename, string& outFile) {
    ifstream f(pFilename);
    bool ret = false;
    if(f.is_open()) {
        string line;
        while(getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        f.close();
        ret = true;
    } else {
    }
    return ret;
}


void ThrowError(const char* pFileName, unsigned int line, const char* pError) {
#ifdef WIN32
    char msg[1000];
    _snprintf_s(msg, sizeof(msg), "%s:%d: %s", pFileName, line, pError);
    MessageBoxA(NULL, msg, NULL, 0);
#else
    fprintf(stderr, "%s:%d: %s\n", pFileName, line, pError);
#endif
}

//////////////////////////////////////////////////////////////////////////
// ÐèÒª¸ÄÐ´
//unsigned int TextureFromFile(const char *path, const string &directory, bool gamma) {
//	string filename = string(path);
//	filename = directory + '/' + filename;
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	int width, height, nrComponents;
//	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//	if(data) {
//		GLenum format;
//		if(nrComponents == 1)
//			format = GL_RED;
//		else if(nrComponents == 3)
//			format = GL_RGB;
//		else if(nrComponents == 4)
//			format = GL_RGBA;
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		stbi_image_free(data);
//	} else {
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//	return textureID;
//}