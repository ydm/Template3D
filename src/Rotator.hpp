#ifndef __T3D_ROTATOR_HPP__
#define __T3D_ROTATOR_HPP__

#include "default.hpp"
#include <AntTweakBar.h>


namespace t3d
{

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

} // namespace

#endif // __T3D_ROTATOR_HPP__
