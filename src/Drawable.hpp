#ifndef __T3D_DRAWABLE_HPP__
#define __T3D_DRAWABLE_HPP__

#include "default.hpp"
#include "shaders.hpp"


namespace t3d
{

class DrawableManager;


/**
 * Drawables are managed by an instance of DrawableManager.
 */
class Drawable
{
public:
    Drawable();
    virtual ~Drawable();

    void setModelMatrix(const GLfloat *const M);
    void setProjectionMatrix(const GLfloat *const M);
    void setViewMatrix(const GLfloat *const M);
    void setUniformFloat(const GLchar *const name, const GLfloat value);
    void setUniformVec2(const GLchar *const name, const GLfloat *const vec);

protected:
    virtual bool init();
    virtual void terminate();
    virtual bool update(const float dt);

    virtual bool addShaders() = 0;
    virtual void drawWithShader() = 0;

    bool addShader(const GLuint type, const std::string& source);

private:
    void draw();

    shaders::Program program_;
    Drawable *next_;

    friend class DrawableManager;
};

} // namespace

#endif // __T3D_DRAWABLE_HPP__
