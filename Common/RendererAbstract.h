//
// Created by Firat Agdas on 3/18/18.
//

#ifndef OPENGLLEARNINGLIBRARY_RENDERERABSTRACT_H
#define OPENGLLEARNINGLIBRARY_RENDERERABSTRACT_H

#include <OpenGL/gl.h>

class RendererAbstract {
public:

    RendererAbstract(bool enabled = true) : m_enabled(enabled) {}
    virtual ~RendererAbstract() {}

    virtual void init() {}
    virtual void update(double deltaTime) {}
    virtual void render(double deltaTime) = 0;
    virtual void beforeUpdate(double deltaTime) {}
    virtual void cleanUp() {}

    void setEnabled(bool value) { m_enabled = value; }
    bool isEnabled() { return m_enabled; }

protected:
    bool m_enabled;
};


#endif //OPENGLLEARNINGLIBRARY_RENDERERABSTRACT_H
