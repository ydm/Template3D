#include "CameraFrustum.hpp"


CameraFrustum::CameraFrustum()
{
}


CameraFrustum::~CameraFrustum()
{
}


bool CameraFrustum::sphereInside(const glm::vec3& pos, const float radius) const
{
    for(int i = 0; i < 6; i++)
    {
        const float dist = planes_[i].distance(pos);
        if (dist < -radius)
        {
            return false; // outside
        }
        else if (dist < radius)
        {
            // return false;
            return true; // intersection
        }
    }
    return true; // inside
}


bool CameraFrustum::sphereInside(const glm::vec4& pos, const float radius) const
{
    return sphereInside(glm::vec3(pos), radius);
}
