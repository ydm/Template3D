#ifndef __PLANE_HPP__
#define __PLANE_HPP__

#include "glm/glm.hpp"
#include <iostream>


// std::ostream& operator<<(std::ostream& os, const Plane& obj);


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

    void setPlane(const glm::vec3& one, const glm::vec3& two, const glm::vec3& three);
    void setPlane(const glm::vec4& one, const glm::vec4& two, const glm::vec4& three);

private:
    float d_;
    glm::vec3 n_;

    friend std::ostream& operator<<(std::ostream& os, const Plane& obj);
};


#endif // __PLANE_HPP__