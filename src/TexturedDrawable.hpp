#ifndef __TEXTURED_DRAWABLE_HPP__
#define __TEXTURED_DRAWABLE_HPP__

#include "BMPReader.hpp"
#include "Drawable.hpp"


class TexturedDrawable : public Drawable
{
public:
	TexturedDrawable();
	virtual ~TexturedDrawable();

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
	BMPReader reader_;
};

#endif // __TEXTURED_DRAWABLE_HPP__
