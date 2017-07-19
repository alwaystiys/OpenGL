#ifndef SHADER_BASIC_H
#define SHADER_BASIC_H
#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Common/lib_math.h"

class ShaderBasic {
public:
    ShaderBasic();
    virtual ~ShaderBasic();
    virtual bool Init();
    void Enable();

    void setUniform1b(const std::string &name, bool value) const;
    void setUniform1i(const std::string &name, int value) const;
    void setUniform1f(const std::string &name, float value) const;

    void setUniform3f(const std::string &name, float v0, float v1, float v2) const;
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const;

    void setUniformVec3f(const std::string &name, vec3);
    void setUniformMatrix4fv(const std::string &name, float* value) const;
    GLuint m_shaderProg;
protected:
    bool AddShader(GLenum shaderType, const char* pFilename, const char* shaderStr);
    bool LinkProgram();
private:
    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;

};




#endif SHADER_BASIC_H