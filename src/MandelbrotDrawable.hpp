#ifndef __MANDELBROT_DRAWABLE_HPP__
#define __MANDELBROT_DRAWABLE_HPP__

#include "Drawable.hpp"


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

#endif // __MANDELBROT_DRAWABLE_HPP__
