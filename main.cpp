#include <iostream>

#include "Common/GLWindowWrapper.h"
#include "Tutorial1/Tutorial1Renderer.h"

int main() {

    GLWindowWrapper window(true);
    window.init();

    window.setSize(1280, 1024);
    window.setTitle("OpenGL GLFW Window.");

    window.build();

    window.addRenderer(new Tutorial1Renderer());

    return window.run();
}