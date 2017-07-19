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

bool ShaderBasic::AddShader(GLenum shaderType, const char* pFilename, const char* shaderStr) {
    std::string s;
    if(shaderStr != NULL) {
        s = shaderStr;
    } else {
        if(!ReadFile(pFilename, s)) {
            fprintf(stderr, "readFile '%s' error\n", pFilename);
            return false;
        }
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


void ShaderBasic::setUniform1b(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_shaderProg, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void ShaderBasic::setUniform1i(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_shaderProg, name.c_str()), value);
}
// ------------------------------------------------------------------------
void ShaderBasic::setUniform1f(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_shaderProg, name.c_str()), value);
}

// ------------------------------------------------------------------------
void ShaderBasic::setUniform3f(const std::string &name, float v0, float v1, float v2) const {
    glUniform3f(glGetUniformLocation(m_shaderProg, name.c_str()), v0, v1, v2);
}

// ------------------------------------------------------------------------
void ShaderBasic::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const {
    glUniform4f(glGetUniformLocation(m_shaderProg, name.c_str()), v0, v1, v2, v3);
}

// ------------------------------------------------------------------------
void ShaderBasic::setUniformMatrix4fv(const std::string &name, float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProg, name.c_str()), 1, GL_FALSE, value);
}

void ShaderBasic::setUniformVec3f(const std::string &name, vec3 v) {
    glUniform3f(glGetUniformLocation(m_shaderProg, name.c_str()), v.x, v.y, v.z);
}
