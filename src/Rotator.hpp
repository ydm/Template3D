#ifndef __ROTATOR_HPP__
#define __ROTATOR_HPP__

#include "glm/glm.hpp"
#include <AntTweakBar.h>


class Rotator
{
public:
    Rotator();
    virtual ~Rotator();

    virtual bool init();
    virtual void terminate();
    virtual glm::mat4 rotate() = 0;

protected:
	glm::vec3 angles_;
	TwBar *bar_;
};

#endif // __ROTATOR_HPP__