//
// Created by Firat Agdas on 3/18/18.
//

#include "GLSLShader.h"
#include "Logger.h"

static inline GLenum getShaderType(GLSLShader::ShaderType type) {
    GLenum shaderType = 0;
    switch (type) {
        case GLSLShader::Vertext:
            shaderType = GL_VERTEX_SHADER;
            break;

        case GLSLShader::Fragment:
            shaderType = GL_FRAGMENT_SHADER;
            break;

        case GLSLShader::Geometry:
            shaderType = GL_GEOMETRY_SHADER_EXT;
            break;

        default:
            Logger::shared().warning("Unhandled shaderType to convert actual GL shader.");
    }

    return shaderType;
}

GLSLShader::GLSLShader()
    : m_program(0)
    , m_shaderList { 0, 0, 0 }
    , m_shaderCount(0)
    , m_inUse(false)
    , m_created(false) {

}

GLSLShader::~GLSLShader() {
    if (m_inUse)
        unuse();

    if (m_created)
        deleteProgram();
}

void GLSLShader::loadFromString(ShaderType type, const char *source) {

    GLint shaderId = glCreateShader(getShaderType(type));

}

void GLSLShader::loadFromFile(ShaderType type, const char *filePath) {

}

void GLSLShader::createAndLinkProgrem() {

}

void GLSLShader::use() {

}

void GLSLShader::unuse() {

}

void GLSLShader::addAttribute(const char *attribute) {

}

void GLSLShader::addUniform(const char *uniform) {

}

GLuint GLSLShader::getAttribute(const char *attribute) {

    return 0;
}

GLuint GLSLShader::getUniform(const char *uniform) {

    return 0;
}

void GLSLShader::deleteProgram() {

}