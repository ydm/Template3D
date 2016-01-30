#include "AxisRotator.hpp"


namespace
{

float rad(const float r)
{
    return r * glm::pi<float>();
}

} // namespace


namespace t3d
{

AxisRotator::AxisRotator()
: Rotator()
{
}


AxisRotator::~AxisRotator()
{
}


bool AxisRotator::init()
{
    // Setup tweak bar
    bar_ = TwNewBar("Axis Rotation");

    // TwDefine(" GLOBAL help='' ");
    // keyIncr=s keyDecr=S
    TwAddVarRW(bar_, "Z", TW_TYPE_FLOAT, &angles_[0], " label='Z' min=-2 max=2 step=0.01 ");
    TwAddVarRW(bar_, "X", TW_TYPE_FLOAT, &angles_[1], " label='X' min=-2 max=2 step=0.01 ");
    TwAddVarRW(bar_, "Y", TW_TYPE_FLOAT, &angles_[2], " label='Y' min=-2 max=2 step=0.01 ");

    return true;
}


glm::mat4 AxisRotator::rotate()
{
    static const glm::vec3 X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z(0.0f, 0.0f, 1.0f);

    return glm::rotate(rad(angles_[0]), Z)
        * glm::rotate(rad(angles_[1]), X)
        * glm::rotate(rad(angles_[2]), Y);
}

} // namespace
