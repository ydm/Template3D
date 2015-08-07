#include "Plane.hpp"
#include "glm/ext.hpp"


std::ostream& operator<<(std::ostream& os, const Plane& obj)
{
    os << "[Plane " << "n=" << glm::to_string(obj.n_) << ", "
                    << "d=" << obj.d_ << "]";
    return os;
}


Plane::Plane()
: d_(0.0f)
, n_(0.0f)
{
}


Plane::Plane(const glm::vec3& one, const glm::vec3& two, const glm::vec3& three)
: d_(0.0f)
, n_(0.0f)
{
    setPlane(one, two, three);
}

Plane::Plane(const glm::vec4& one, const glm::vec4& two, const glm::vec4& three)
: d_(0.0f)
, n_(0.0f)
{
    setPlane(one, two, three);
}


Plane::~Plane()
{
}


Plane& Plane::operator=(const Plane& other)
{
    if (this != &other)
    {
        d_ = other.d_;
        n_ = other.n_;
    }
    return *this;
}


float Plane::distance(const glm::vec3& v) const
{
    return glm::dot(v, n_) + d_;
}


const glm::vec3&
Plane::getNormal() const
{
    return n_;
}


void Plane::setPlane(const glm::vec3& one, const glm::vec3& two, const glm::vec3& three)
{
    const glm::vec3& v = two - one;
    const glm::vec3& u = three - one;
    // n_ = glm::fastNormalize(glm::cross(v, u));
    n_ = glm::normalize(glm::cross(v, u));
    d_ = -glm::dot(n_, one);
}


void Plane::setPlane(const glm::vec4& one, const glm::vec4& two, const glm::vec4& three)
{
    setPlane(glm::vec3(one), glm::vec3(two), glm::vec3(three));
}
