#include "Drawable.hpp"
#include <iostream>


Drawable::Drawable()
: program_()
, next_(nullptr)
{
}


Drawable::~Drawable()
{
	// Prevent errors by nullifying the next pointer,
	// as it should not be used after object deletion.
	next_ = nullptr;
}


bool Drawable::init()
{
	static const GLfloat I[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	if (program_.create() && addShaders() && program_.link())
	{
		setProjectionMatrix(I);
		setViewMatrix(I);
		setModelMatrix(I);
		return true;
	}
	return false;
}


void Drawable::terminate()
{
    program_.release();
}


void Drawable::draw()
{
    program_.use();
    drawWithShader();
}


bool Drawable::update(const float dt)
{
	return false;
}


void Drawable::setProjectionMatrix(const GLfloat *const M)
{
	program_.umat4("u_projectionMatrix", M);
}


void Drawable::setViewMatrix(const GLfloat *const M)
{
	program_.umat4("u_viewMatrix", M);
}


void Drawable::setModelMatrix(const GLfloat *const M)
{
	program_.umat4("u_modelMatrix", M);
}


void Drawable::setUniformFloat(const GLchar *const name, const GLfloat value)
{
	program_.ufloat(name, value);
}


void Drawable::setUniformVec2(const GLchar *const name, const GLfloat *const vec)
{
	program_.uvec2(name, vec);
}


bool Drawable::addShader(const GLuint type, const std::string& source)
{
	return program_.attachShader(type, source);
}
