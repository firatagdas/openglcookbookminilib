//
// Created by Firat Agdas on 3/17/18.
//

#ifndef OPENGLLEARNINGLIBRARY_GLFWWINDOW_H
#define OPENGLLEARNINGLIBRARY_GLFWWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <glm/glm.hpp>

#include "Common.h"
#include <vector>
#include "RendererAbstract.h"
#include "Logger.h"

LOGGER_DECLARE_CATEGORY(GLWindow)

class GLWindowWrapper {
public:

    explicit GLWindowWrapper(bool debugMode = false);

    void setSize(int width, int height);
    void setTitle(const char *title);

    void addRenderer(RendererAbstract *renderer);
    void resetRendererList();

    bool init();
    bool build();

    int run();

private:
    void initRenderList();
    void updateRenderList(float deltaTime);
    void renderList(float deltaTime);
    void beforeUpdateRenderList(float deltaTime);
    void cleanUpRendererList();



private:
    bool m_debug;
    GLFWwindow *m_handle;
    int m_width;
    int m_height;
    char m_title[100];
    std::vector<RendererAbstract *> m_rendererList;
};


#endif //OPENGLLEARNINGLIBRARY_GLFWWINDOW_H
