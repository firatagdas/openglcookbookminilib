//
// Created by Firat Agdas on 3/18/18.
//

#include "GLSLShader.h"
#include <fstream>

LOGGER_CATEGORY(GLSLShader, "GLSL Shader Management")

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
            logCWarning(GLSLShader, "Unhandled shaderType to convert actual GL shader.");
    }

    return shaderType;
}

static inline const char *getShaderTypeAllocatedString(GLSLShader::ShaderType type) {
    auto shaderTypeString = new char[15];
    switch (type) {
        case GLSLShader::Vertext:
            strcpy(shaderTypeString, "VERTEX_SHADER");
            break;

        case GLSLShader::Fragment:
            strcpy(shaderTypeString, "FRAGMENT_SHADER");
            break;

        case GLSLShader::Geometry:
            strcpy(shaderTypeString, "GEOMETRY_SHADER");
            break;

        default:
            logCWarning(GLSLShader, "Unhandled shaderType to convert actual GL shader.");
    }

    return shaderTypeString;
}

GLSLShader::GLSLShader(bool debug)
    : m_program(0)
    , m_shaderList { 0, 0, 0 }
    , m_shaderCount(0)
    , m_inUse(false)
    , m_created(false)
    , m_debug(debug) {

}

GLSLShader::~GLSLShader() {
    if (m_inUse)
        unuse();

    if (m_created)
        deleteProgram();
}

void GLSLShader::loadFromString(ShaderType type, const char *source) {
    if (m_created) {
        logCDebug(GLSLShader, "Shader Program already created. Cannot load a shader.");
        return;
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Shader compiling: %s", source);

    GLuint shaderId = glCreateShader(getShaderType(type));

    glShaderSource(shaderId, 1, &source, nullptr);
    glCompileShader(shaderId);

    GLint status = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

        auto log = new char[logLength];
        glGetShaderInfoLog(shaderId, logLength, nullptr, log);

        logCErrorV(GLSLShader, "Shader compile error: %s\nCode: %s", log, source);
        return;
    }

    if (m_debug)
        logCDebug(GLSLShader, "Shader compiling successful.");

    m_shaderCount++;
    m_shaderList[type] = shaderId;
}

void GLSLShader::loadFromFile(ShaderType type, const char *filePath) {
    std::ifstream stream(filePath, std::ifstream::in);
    if (stream) {
        if (m_debug)
            logCDebugV(GLSLShader, "Shader will start compiling from file: %s", filePath);

        std::string line, context;
        while (std::getline(stream, line)) {
            context.append(line);
            context.append("\r\n");
        }

        loadFromString(type, context.c_str());
    } else if (m_debug) {
        logCDebugV(GLSLShader, "Shader file cannot opened: %s", filePath);
    }
}

void GLSLShader::createAndLinkProgram() {
    if (m_created) {
        logCWarning(GLSLShader, "Program already created & linked. Cannot continue.");
        return;
    }

    m_program = glCreateProgram();
    if (m_debug)
        logCDebugV(GLSLShader, "Creating Shader Program: %d", m_program);

    if (m_shaderList[Vertext]) {
        glAttachShader(m_program, m_shaderList[Vertext]);
        if (m_debug) {
            auto shaderTypeStr = getShaderTypeAllocatedString(Vertext);
            logCDebugV(GLSLShader, "Attaching %s to Program: %d", shaderTypeStr, m_program);
            delete shaderTypeStr;
        }
    }

    if (m_shaderList[Fragment]) {
        glAttachShader(m_program, m_shaderList[Fragment]);
        if (m_debug) {
            auto shaderTypeStr = getShaderTypeAllocatedString(Fragment);
            logCDebugV(GLSLShader, "Attaching %s to Program: %d", shaderTypeStr, m_program);
            delete shaderTypeStr;
        }
    }

    if (m_shaderList[Geometry]) {
        glAttachShader(m_program, m_shaderList[Geometry]);
        if (m_debug) {
            auto shaderTypeStr = getShaderTypeAllocatedString(Geometry);
            logCDebugV(GLSLShader, "Attaching %s to Program: %d", shaderTypeStr, m_program);
            delete shaderTypeStr;
        }
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Linking Program: %d", m_program);

    glLinkProgram(m_program);

    GLint status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        GLint logLength = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

        auto log = new char[logLength];
        glGetProgramInfoLog(m_program, logLength, nullptr, log);

        logCErrorV(GLSLShader, "Program link error %s.", log);
        return;
    }

    if (m_shaderList[Vertext]) {
        glDeleteShader(m_shaderList[Vertext]);
        m_shaderList[Vertext] = 0;

        if (m_debug) {
            auto shaderTypeStr = getShaderTypeAllocatedString(Vertext);
            logCDebugV(GLSLShader, "Deleting %s", shaderTypeStr);
            delete shaderTypeStr;
        }
    }

    if (m_shaderList[Fragment]) {
        glDeleteShader(m_shaderList[Fragment]);
        m_shaderList[Fragment] = 0;

        if (m_debug) {
            auto shaderTypeStr = getShaderTypeAllocatedString(Fragment);
            logCDebugV(GLSLShader, "Deleting %s", shaderTypeStr);
            delete shaderTypeStr;
        }
    }

    if (m_shaderList[Geometry]) {
        glDeleteShader(m_shaderList[Geometry]);
        m_shaderList[Geometry] = 0;

        if (m_debug) {
            auto shaderTypeStr = getShaderTypeAllocatedString(Geometry);
            logCDebugV(GLSLShader, "Deleting %s", shaderTypeStr);
            delete shaderTypeStr;
        }
    }

    m_created = true;
}

void GLSLShader::use() {
    if (!m_created) {
        logCWarning(GLSLShader, "Program is not exists yet. Please use createAndLinkProgram() method first. Cannot use use().");
        return;
    }

    if (m_inUse) {
        logCWarning(GLSLShader, "Program is in use already.");
        return;
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Using Shader Program: %d", m_program);

    glUseProgram(m_program);
    m_inUse = true;
}

void GLSLShader::unuse() {
    if (!m_created) {
        logCWarning(GLSLShader, "Program is not exists yet. Please use createAndLinkProgram() method first. Cannot use unuse().");
        return;
    }

    if (!m_inUse) {
        logCWarning(GLSLShader, "Program is not in use already.");
        return;
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Unusing Shader Program: %d", m_program);

    glUseProgram(0);
    m_inUse = false;
}

void GLSLShader::addAttribute(const char *attribute) {
    if (!m_created) {
        logCWarning(GLSLShader, "Program is not exists yet. Please use createAndLinkProgram() method first. Cannot use addAttribute().");
        return;
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Adding attribute: %s", attribute);

    m_attributeMap[attribute] = glGetAttribLocation(m_program, attribute);
}

void GLSLShader::addUniform(const char *uniform) {
    if (!m_created) {
        logCWarning(GLSLShader, "Program is not exists yet. Please use createAndLinkProgram() method first. Cannot use addUniform().");
        return;
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Adding uniform: %s", uniform);

    m_uniformMap[uniform] = glGetUniformLocation(m_program, uniform);
}

GLint GLSLShader::getAttribute(const char *attribute) {
    if (!m_attributeMap.find(attribute) == m_attributeMap.end()) {
        logCWarningV(GLSLShader, "Attribute is not found: %s.", attribute);
        return -1;
    }

    return m_attributeMap[attribute];
}

GLint GLSLShader::getUniform(const char *uniform) {
    if (!m_uniformMap.find(uniform) == m_uniformMap.end()) {
        logCWarningV(GLSLShader, "Uniform is not found: %s.", uniform);
        return -1;
    }

    return m_uniformMap[uniform];
}

void GLSLShader::deleteProgram() {
    if (!m_created) {
        logCWarning(GLSLShader, "Program is not exists yet. Please use createAndLinkProgram() method first. Cannot use deleteProgram().");
        return;
    }

    if (m_debug)
        logCDebugV(GLSLShader, "Deleting Shader Program: %d", m_program);

    if (m_inUse)
        unuse();

    glDeleteProgram(m_program);
    m_created = false;
}