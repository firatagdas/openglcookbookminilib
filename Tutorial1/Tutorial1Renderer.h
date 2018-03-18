//
// Created by Firat Agdas on 3/18/18.
//

#ifndef OPENGLLEARNINGLIBRARY_TUTORIAL1RENDERER_H
#define OPENGLLEARNINGLIBRARY_TUTORIAL1RENDERER_H

#include "../Common/RendererAbstract.h"


class Tutorial1Renderer : public RendererAbstract {
public:
    Tutorial1Renderer(bool enabled = true) : RendererAbstract(enabled) {}
    void render(double deltaTime);
};


#endif //OPENGLLEARNINGLIBRARY_TUTORIAL1RENDERER_H
