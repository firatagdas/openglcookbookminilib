//
// Created by Firat Agdas on 3/17/18.
//

#include "GLWindowWrapper.h"
#include "Logger.h"
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>


#define FPS_MAX 60
#define MS_PER_UPDATE (1.0 / FPS_MAX)

LOGGER_CATEGORY(GLWindow, "GL Window Management")

GLWindowWrapper::GLWindowWrapper(bool debugMode)
        : m_debug(debugMode)
        , m_handle(nullptr)
        , m_width(1024)
        , m_height(768) {

    const char *title = "Default OpenGL Window";
    strcpy(m_title, title);
}

bool GLWindowWrapper::init() {
    int result = glfwInit();
    if (!result) {
        if (m_debug)
            logCError(GLWindow, "GLFW initialization failed.");
    } else if (m_debug) {
        logCDebugV(GLWindow, "GLFW successfully initialized. GLFW Version: %s.", glfwGetVersionString());
    }

    return result == GLFW_TRUE;
}

void GLWindowWrapper::setSize(int width, int height) {
    if (m_width <= 0 || m_height <= 0) {
        if (!m_debug)
            logCWarning(GLWindow, "Width & Height cannot be negative or zero.");

        return;
    }

    if (m_width != width || m_height != height) {
        m_width = width;
        m_height = height;

        if (m_debug)
            logCDebugV(GLWindow, "Setting window size to %dx%d.", m_width, m_height);

        if (m_handle)
            glfwSetWindowSize(m_handle, m_width, m_height);

    } else if (m_debug) {
        logCDebugV(GLWindow, "Window is the same size to with given %dx%d.", m_width, m_height);
    }
}

void GLWindowWrapper::setTitle(const char *title) {
    auto message = (char *) title;
    if (strlen(message) > 150) {
        message[149] = '\0';
        message[148] = '.';
        message[147] = '.';
        message[146] = '.';
    }

    strcpy(m_title, message);
    if (m_handle)
        glfwSetWindowTitle(m_handle, m_title);
}

bool GLWindowWrapper::build() {
    if (m_handle) {
        if (m_debug)
            logCWarning(GLWindow, "There is a window already. Cannot be rebuilt.");

        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (m_debug)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    m_handle = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (!m_handle) {
        if (m_debug)
            logCError(GLWindow, "Window couldn't be created.");

        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_handle);
    glfwSetInputMode(m_handle, GLFW_STICKY_KEYS, GLFW_TRUE);

    glewExperimental = GL_TRUE;
    GLenum glewErrorStatus = glewInit();
    if (glewErrorStatus != GLEW_OK) {
        logCErrorV(GLWindow, "Unable to initialize GLEW. Error: %s\n", glewGetErrorString(glewErrorStatus));

        glfwTerminate();

        m_handle = nullptr;
        return false;
    }

    return true;
}

void GLWindowWrapper::addRenderer(RendererAbstract *renderer) {
    m_rendererList.push_back(renderer);
}

void GLWindowWrapper::resetRendererList() {
    for (auto renderer: m_rendererList) {
        delete renderer;
    }

    m_rendererList.clear();
}

void GLWindowWrapper::initRenderList() {
    for (auto renderer: m_rendererList) {
        renderer->init();
    }
}

void GLWindowWrapper::updateRenderList(float deltaTime) {
    for (auto renderer: m_rendererList) {
        if (renderer->isEnabled())
            renderer->update(deltaTime);
    }
}

void GLWindowWrapper::renderList(float deltaTime) {
    for (auto renderer: m_rendererList) {
        if (renderer->isEnabled())
            renderer->render(deltaTime);
    }
}

void GLWindowWrapper::beforeUpdateRenderList(float deltaTime) {
    for (auto renderer: m_rendererList) {
        if (renderer->isEnabled())
            renderer->beforeUpdate(deltaTime);
    }
}

void GLWindowWrapper::cleanUpRendererList() {
    for (auto renderer: m_rendererList) {
        renderer->cleanUp();
    }
}


int GLWindowWrapper::run() {
    int result = 0;
    if (!m_handle) {
        if (m_debug)
            logCCritical(GLWindow, "Window is not created yet. So running does not make sense.");

        result = 1;
    } else {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        initRenderList();

        auto previousTime = glfwGetTime();
        double deltaTime = 0.0f;
        double currentTime = 0.0f;

        do {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            currentTime = glfwGetTime();
            deltaTime = (currentTime - previousTime);
            previousTime = currentTime;

            beforeUpdateRenderList(deltaTime);

            updateRenderList(deltaTime);

            renderList(deltaTime);

            glfwSwapBuffers(m_handle);
            glfwPollEvents();

            if (deltaTime < MS_PER_UPDATE)
                usleep((useconds_t) ((MS_PER_UPDATE - deltaTime) * 1000));

        } while (glfwGetKey(m_handle, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(m_handle));

        resetRendererList();
        cleanUpRendererList();

        glfwTerminate();
    }

    return result;
}

