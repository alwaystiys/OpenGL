#ifndef SHADER_BASIC_H
#define SHADER_BASIC_H
#include <list>
#include <GL/glew.h>

class ShaderBasic {
public:
    ShaderBasic();
    virtual ~ShaderBasic();
    virtual bool Init();
    void Enable();

    GLuint m_shaderProg;
protected:
    bool AddShader(GLenum shaderType, const char* pFilename, const char* shaderStr);
    bool LinkProgram();
private:
    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;

};




#endif SHADER_BASIC_H