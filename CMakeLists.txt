cmake_minimum_required(VERSION 3.9)
project(OpenGLLearningLibrary)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
set(GLM_PATH /usr/local/Cellar/glm/0.9.8.5)
set(BUILD_SHARED_LIBS ON)

include_directories(${GLM_PATH}/include)
link_directories(${GLM_PATH}/lib ${GLFW_PATH}/lib)

FIND_PACKAGE(OpenGL REQUIRED)
if(OpenGL_FOUND)
    link_directories(${OpenGL_LIBRARY_DIRS})
    include_directories(${OpenGL_INCLUDE_DIR})
endif(OpenGL_FOUND)

FIND_PACKAGE(glfw3 REQUIRED)
if(glfw3_FOUND)
    link_directories(${glfw3_LIBRARY_DIRS})
    include_directories(${glfw3_INCLUDE_DIR})
endif(glfw3_FOUND)

FIND_PACKAGE(glew REQUIRED)
if(glew_FOUND)
    link_directories(${glew_LIBRARY_DIRS})
    include_directories(${glew_INCLUDE_DIR})
endif(glew_FOUND)


add_executable(OpenGLLearningLibrary main.cpp Common/GLWindowWrapper.cpp Common/GLWindowWrapper.h Common/Common.h Common/Logger.cpp Common/Logger.h Common/RendererAbstract.h Tutorial1/Tutorial1Renderer.cpp Tutorial1/Tutorial1Renderer.h Common/GLSLShader.cpp Common/GLSLShader.h)
target_link_libraries(OpenGLLearningLibrary glew glfw3)