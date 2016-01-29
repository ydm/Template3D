#ifndef __T3D_PLANE_HPP__
#define __T3D_PLANE_HPP__

#include "default.hpp"


namespace t3d
{

/**
 *
 */
class Plane
{
public:
    Plane();
    Plane(const glm::vec3& one, const glm::vec3& two, const glm::vec3& three);
    Plane(const glm::vec4& one, const glm::vec4& two, const glm::vec4& three);
    virtual ~Plane();
    Plane& operator=(const Plane& other);
    
    float distance(const glm::vec3& v) const;
    const glm::vec3& getNormal() const;

    void setPlane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    void setPlane(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c);

private:
    float d_;
    glm::vec3 n_;

    friend std::ostream& operator<<(std::ostream& os, const Plane& obj);
};

} // namespace


#endif // __T3D_PLANE_HPP__
