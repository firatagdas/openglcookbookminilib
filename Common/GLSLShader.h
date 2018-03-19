//
// Created by Firat Agdas on 3/18/18.
//

#ifndef OPENGLLEARNINGLIBRARY_GLSLSHADER_H
#define OPENGLLEARNINGLIBRARY_GLSLSHADER_H

#include <string>
#include <OpenGL/gl.h>
#include <map>
#include <vector>
#include "Logger.h"

LOGGER_DECLARE_CATEGORY(GLSLShader)


class GLSLShader {
public:
    enum ShaderType {
        Vertext = 0,
        Fragment,
        Geometry
    };

    GLSLShader(bool debug = false);
    ~GLSLShader();

    void loadFromString(ShaderType type, const char *source);
    void loadFromFile(ShaderType type, const char *filePath);

    void createAndLinkProgram();

    void use();
    void unuse();

    void addAttribute(const char *attribute);
    void addUniform(const char *uniform);

    GLint getAttribute(const char *attribute);
    GLint getUniform(const char *uniform);

    void deleteProgram();

private:
    GLuint m_program;

    GLuint m_shaderList[3];
    int m_shaderCount;

    std::map<const char *, GLint> m_attributeMap;
    std::map<const char *, GLint> m_uniformMap;

    bool m_inUse;
    bool m_created;

    bool m_debug;
};


#endif //OPENGLLEARNINGLIBRARY_GLSLSHADER_H
