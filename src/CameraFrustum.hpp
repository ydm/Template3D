#ifndef __CAMERA_FRUSTUM_HPP__
#define __CAMERA_FRUSTUM_HPP__

#include "Plane.hpp"

class Camera;


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


#endif // __CAMERA_FRUSTUM_HPP__