//
// Created by Firat Agdas on 3/18/18.
//

#ifndef OPENGLLEARNINGLIBRARY_GLSLSHADER_H
#define OPENGLLEARNINGLIBRARY_GLSLSHADER_H

#include <string>
#include <OpenGL/gl.h>
#include <map>
#include <vector>

class GLSLShader {
public:
    enum ShaderType {
        Vertext,
        Fragment,
        Geometry
    };

    GLSLShader();
    ~GLSLShader();

    void loadFromString(ShaderType type, const char *source);
    void loadFromFile(ShaderType type, const char *filePath);

    void createAndLinkProgrem();

    void use();
    void unuse();

    void addAttribute(const char *attribute);
    void addUniform(const char *uniform);

    GLuint getAttribute(const char *attribute);
    GLuint getUniform(const char *uniform);

    void deleteProgram();

private:
    GLuint m_program;

    GLuint m_shaderList[3];
    int m_shaderCount;

    std::map<const char *, GLuint> m_attributeMap;
    std::map<const char *, GLuint> m_uniformMap;

    bool m_inUse;
    bool m_created;
};


#endif //OPENGLLEARNINGLIBRARY_GLSLSHADER_H
