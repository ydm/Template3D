#ifndef __T3D_TYPES_HPP__
#define __T3D_TYPES_HPP__

#include "default.hpp"


namespace t3d
{

/**
 * Not used yet.
 */
class Ray
{
public:
    Ray();
    ~Ray();

private:
    glm::vec3 position_;
    glm::vec3 direction_;
};

} // namespace

#endif // __T3D_TYPES_HPP__
