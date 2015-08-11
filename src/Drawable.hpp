#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "shaders.hpp"

class DrawableManager;

class Drawable
{
public:
    Drawable();
    ~Drawable();

    virtual bool init();
    virtual void terminate();

    virtual void draw();
	virtual bool update(const float dt);

    virtual void setProjectionMatrix(const GLfloat *const M);
    virtual void setViewMatrix(const GLfloat *const M);
	virtual void setModelMatrix(const GLfloat *const M);

protected:
	virtual bool addShaders() = 0;
	virtual void drawWithShader() = 0;

    bool addShader(const GLuint type, const std::string& source);

private:
    shaders::Program program_;
	Drawable *next_;

	friend class DrawableManager;
};

#endif // __DRAWABLE_HPP__
