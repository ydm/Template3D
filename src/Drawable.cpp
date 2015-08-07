#include "Drawable.hpp"
#include <iostream>


Drawable::Drawable()
: program_()
{
}


Drawable::~Drawable()
{
}


bool Drawable::init()
{
    return program_.create();
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


void Drawable::setProjectionMatrix(const glm::mat4& M)
{

}


void Drawable::setViewMatrix(const glm::mat4& M)
{

}


void Drawable::addShader(const GLuint type, const std::string& source)
{
    if (!program_.attachShader(type, source))
    {
        // TODO
    }
}
