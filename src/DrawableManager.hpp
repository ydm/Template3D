#ifndef __DRAWABLE_MANAGER_HPP__
#define __DRAWABLE_MANAGER_HPP__

#include "Drawable.hpp"


class DrawableManager
{
public:
	DrawableManager();
	~DrawableManager();

	bool init();
	void terminate();

	void addDrawable(Drawable *const drawable);
	void draw();
	bool update(const float dt);

	void setProjectionMatrix(const GLfloat *const M);
	void setViewMatrix(const GLfloat *const M);

private:
	Drawable *head_;
	Drawable *tail_;
};

#endif // __DRAWABLE_MANAGER_HPP__
