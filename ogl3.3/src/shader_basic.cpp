#include "Common/shader_basic.h"
#include "Common/basic_util.h"
#include <stdio.h>
#include <string>




ShaderBasic::ShaderBasic() {
    m_shaderProg = 0;
}

ShaderBasic::~ShaderBasic() {
    if(m_shaderProg != 0) {
        glDeleteProgram(m_shaderProg);
        m_shaderProg = 0;
    }
}

bool ShaderBasic::Init() {
    m_shaderProg = glCreateProgram();
    if(m_shaderProg == 0) {
        fprintf(stderr, "Error creeting shader program\n");
        return false;
    }
    return true;
}

bool ShaderBasic::AddShader(GLenum shaderType, const char* pFilename) {
    std::string s;
    if(!ReadFile(pFilename, s)) {
        fprintf(stderr, "readFile '%s' error\n", pFilename);
        return false;
    }
    GLuint shaderObj = glCreateShader(shaderType);
    if(shaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", shaderType);
        return false;
    }
    m_shaderObjList.push_back(shaderObj);
    const GLchar* p[1] = {s.c_str()};
    GLint length[1] = {(GLint)s.size()};
    glShaderSource(shaderObj, 1, p, length);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
        fprintf(stderr, "Error compiling '%s':'%s'\n", pFilename, infoLog);
        return false;
    }
    glAttachShader(m_shaderProg, shaderObj);
    return true;
}

bool ShaderBasic::LinkProgram() {
    GLint success;
    GLchar infoLog[1024];
    glLinkProgram(m_shaderProg);
    glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shaderProg, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", infoLog);
        return false;
    }
    glValidateProgram(m_shaderProg);
    glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shaderProg, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", infoLog);
    }
    for(ShaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++) {
        glDeleteShader(*it);
    }
    m_shaderObjList.clear();
    return GLCheckError();
}

void ShaderBasic::Enable() {
    glUseProgram(m_shaderProg);
}

