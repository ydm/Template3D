#ifndef __TRIPOD_DRAWABLE_HPP__
#define __TRIPOD_DRAWABLE_HPP__

#include "Drawable.hpp"
#include "Rotator.hpp"


class TripodDrawable : public Drawable
{
public:
	TripodDrawable(const float scale = 1.0f, Rotator *const rotator = nullptr);
	virtual ~TripodDrawable();

	virtual bool init() override;
	virtual void terminate() override;

	virtual bool update(const float dt) override;

        void setColors(float xr, float xg, float xb,
                       float yr, float yg, float yb,
                       float zr, float zg, float zb);
        void setPosition(const glm::vec3& pos);

protected:
	virtual bool addShaders() override;
	virtual void drawWithShader() override;

private:
	Rotator *const rotator_;
	const float scale_;
	GLuint vao_;
        GLuint vbo_[2];
	glm::mat4 M_;
        GLfloat colors_[18];
};

#endif // __TRIPOD_DRAWABLE_HPP__
