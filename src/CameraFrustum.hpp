#ifndef __T3D_CAMERA_FRUSTUM_HPP__
#define __T3D_CAMERA_FRUSTUM_HPP__

#include "Plane.hpp"


namespace t3d
{

// Camera is declared as a friend class and has to be
// forward-declared.
class Camera;

/**
 *
 */
class CameraFrustum
{
public:
    CameraFrustum();
    virtual ~CameraFrustum();

    bool sphereInside(const glm::vec3& pos, const float radius) const;
    bool sphereInside(const glm::vec4& pos, const float radius) const;

private:
    Plane planes_[6];
    friend class Camera;
};

} // namespace


#endif // __T3D_CAMERA_FRUSTUM_HPP__
