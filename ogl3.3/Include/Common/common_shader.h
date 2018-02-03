#ifndef COMMON_SHADER_H
#define COMMON_SHADER_H
#include "Common/shader_basic.h"

class CommonShader : public ShaderBasic {
public:
    CommonShader(const char *vertexShaderSource, const char *fragmentShaderSource, const char *vsFilePath, const char *fsFilePath);
    virtual bool Init();
private:
    const char *vertexShaderSource;
    const char *fragmentShaderSource;
    const char *vsFilePath;
    const char *fsFilePath;
};

#endif COMMON_SHADER_H