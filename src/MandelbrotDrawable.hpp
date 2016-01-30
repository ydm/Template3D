#ifndef __T3D_MANDELBROT_DRAWABLE_HPP__
#define __T3D_MANDELBROT_DRAWABLE_HPP__

#include "Drawable.hpp"


namespace t3d
{

class MandelbrotDrawable : public Drawable
{
public:
    MandelbrotDrawable();
    virtual ~MandelbrotDrawable();

    virtual bool init() override;
    virtual void terminate() override;

    virtual bool update(const float dt) override;
    void setPosition(const glm::vec3& pos);

protected:
    virtual bool addShaders() override;
    virtual void drawWithShader() override;

private:
    GLuint vao_;
    GLuint vbo_[2];
    glm::mat4 M_;
};

} // namespace

#endif // __T3D_MANDELBROT_DRAWABLE_HPP__
