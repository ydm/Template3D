#ifndef __T3D_AXIS_ROTATOR_HPP__
#define __T3D_AXIS_ROTATOR_HPP__

#include "Rotator.hpp"


namespace t3d
{

class AxisRotator : public Rotator
{
public:
    AxisRotator();
    virtual ~AxisRotator();

    virtual bool init() override;
    virtual glm::mat4 rotate() override;
};

} // namespace

#endif // __T3D_ROTATOR_HPP__
