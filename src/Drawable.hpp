#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "shaders.hpp"


class Drawable
{
    Drawable();
    ~Drawable();

    virtual bool init();
    virtual void terminate();

    virtual void draw();

    virtual void setProjectionMatrix(const glm::mat4& M);
    virtual void setViewMatrix(const glm::mat4& M);

protected:
    void addShader(const GLuint type, const std::string& source);
    virtual void drawWithShader() = 0;

private:
    shaders::Program program_;
};

#endif // __DRAWABLE_HPP__
