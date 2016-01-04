#include "EulerRotator.hpp"
#include "glm/ext.hpp"


EulerRotator::EulerRotator()
: Rotator()
{
}


EulerRotator::~EulerRotator()
{
}


bool EulerRotator::init()
{
    // Setup tweak bar
    bar_ = TwNewBar("Euler Rotation");
    
    // TwDefine(" GLOBAL help='' ");
    // keyIncr=s keyDecr=S
    TwAddVarRW(bar_, "heading", TW_TYPE_FLOAT, &angles_[0], " label='Heading (Y)' min=-2 max=2 step=0.01 ");
    TwAddVarRW(bar_, "pitch", TW_TYPE_FLOAT, &angles_[1], " label='Pitch (X)' min=-2 max=2 step=0.01 ");
    TwAddVarRW(bar_, "bank", TW_TYPE_FLOAT, &angles_[2], " label='Bank (Z)' min=-2 max=2 step=0.01 ");

    return true;
}


glm::mat4 EulerRotator::rotate()
{
    static const glm::vec3 X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z(0.0f, 0.0f, 1.0f);

    return glm::rotate(glm::radians(angles_[0]), Y)
         * glm::rotate(glm::radians(angles_[1]), X)
         * glm::rotate(glm::radians(angles_[2]), Z);
}
