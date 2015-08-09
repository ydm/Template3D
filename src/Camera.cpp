#include "Camera.hpp"
#include <algorithm>
#include "glm/ext.hpp"


// ========================
// Constants
// ========================
namespace
{
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 3000.0f;
    const float FOVY = glm::radians(70.0f);
    // const float MAXPOS = 100.0f;
}


// ========================
// Helpers
// ========================

glm::vec2 computePlaneSize(const float fovyRad, const float distance, const float aspect)
{
    const float height = 2.0f * distance * glm::tan(fovyRad / 2);
    const float width = height * aspect;
    return glm::vec2(width, height);
}


// ========================
// Camera
// ========================

Camera::Camera()
: mousePosition_(-1, -1)
, position_(0, 0, 5, 1)
, projection_(1.0)
, R_()
, Rinv_()
, rotation_()
, speed_(3.0f)
, velocity_()
, view_(1.0)
, viewportSize_(800, 600)
{
    std::fill(directions_, directions_ + 6, false);
}


Camera::~Camera()
{
}


bool Camera::update(const float dt)
{
    bool changed = false;
    for (unsigned i = 0; i < 6; i++)
    {
        // ydm TODO: MAXPOS CHECK?
        if (directions_[i])
        {
            position_ += Rinv_ * getVelocity(i) * dt;
            changed = true;
        }
    }

    // Always returns `true` when mouse is enabled
    if (changed || mouseEnabled_)
    {
        updateViewMatrix();
        return true;
    }
    return false;
}


// ========================
// Walking
// ========================

void Camera::walk       (const enum Direction dir) {directions_[dir] =  true;}
void Camera::stopWalking(const enum Direction dir) {directions_[dir] = false;}


// ========================
// Rotating with mouse
// ========================

void Camera::enableMouse()
{
    mouseEnabled_ = true;
}


void Camera::mouseMotion(const int x, const int y)
{
    static const float SENSITIVITY = 1.0f;

    if (mouseEnabled_)
    {
        // Compute steps
        const int sx = x - mousePosition_[0];
        const int sy = y - mousePosition_[1];

        // With a single swipe from one edge of the viewport to the other,
        // user should be able to rotate for a full pi about his own axes.
        // I define this to be sensitivity of 1.
        const float rx = static_cast<float>(sy) / viewportSize_.x * glm::pi<float>() * SENSITIVITY;
        const float ry = static_cast<float>(sx) / viewportSize_.y * glm::pi<float>() * SENSITIVITY;
        addToRotation(rx, ry, 0);
    }

    mousePosition_[0] = x;
    mousePosition_[1] = y;
}


void Camera::disableMouse()
{
    mouseEnabled_ = false;
    mousePosition_[0] = -1;
    mousePosition_[1] = -1;
}


// ========================
// Setters
// ========================

void Camera::setPosition(const glm::vec3& pos)
{
    position_ = glm::vec4(pos, 1);
    updateViewMatrix();
}


// ========================
// Parameters
// ========================

float Camera::getMovementSpeed() const
{
    return speed_;
}


void Camera::setMovementSpeed(const float speed)
{
    speed_ = speed;
}


void Camera::setViewportSize(const int w, const int h)
{
    viewportSize_.x = w;
    viewportSize_.y = h;
    projection_ = glm::perspective(FOVY, getAspectRatio(), NEAR_PLANE, FAR_PLANE);
}


// ========================
// Ray functions
// ========================

glm::vec3 Camera::getLookDirection() const
{
    static const glm::vec4 DIR(0.0f, 0.0f, -1.0f, 0.0f);
    const glm::vec3& dir = glm::vec3(Rinv_ * DIR);
    return glm::fastNormalize(dir);
}


// Big thanks to http://schabby.de/picking-opengl-ray-tracing/
glm::vec3 Camera::getMouseRay(const int x, const int y) const
{
    // 3D
    const glm::vec2& half = computePlaneSize(glm::radians(FOVY), NEAR_PLANE, getAspectRatio()) / 2.0f;

    // 2D
    const float windowHalfWidth = static_cast<float>(viewportSize_.x) / 2.0f;
    const float windowHalfHeight = static_cast<float>(viewportSize_.y) / 2.0f;
    const float xp =  x / windowHalfWidth  - 1.0f;
    const float yp = -y / windowHalfHeight + 1.0f;

    // const glm::vec4 directionInCameraSpace(0.0f, 0.0f, -1.0f, 1.0f);
    const glm::vec4 directionInCameraSpace(xp * half.x, yp * half.y, -NEAR_PLANE, 0);
    const glm::vec4 directionInWorldSpace = Rinv_ * directionInCameraSpace;
    const glm::vec3 v3 = glm::vec3(directionInWorldSpace);
    
    // return glm::fastNormalize(v3);
    return glm::normalize(v3);
}


const glm::vec4& Camera::getPosition() const
{
    return position_;
}


// ========================
// Matrix getters
// ========================

const glm::mat4& Camera::getViewMatrix() const
{
	return view_;
}


const glm::mat4& Camera::getProjectionMatrix() const
{
	return projection_;
}


// ========================
// Visibility checking
// ========================

CameraFrustum *
Camera::getCameraFrustum() const
{
    static const glm::vec4 DIR(0.0f, 0.0f, -1.0f, 0.0f);
    static const glm::vec4 RIGHT(1.0f, 0.0f, 0.0f, 0.0f);
    static const glm::vec4 UP(0.0f, 1.0f, 0.0f, 0.0f);

    const glm::vec3 cameraPos(getPosition());

    const glm::vec3& dir = glm::vec3(Rinv_ * DIR);
    const glm::vec3& right = glm::vec3(Rinv_ * RIGHT);
    const glm::vec3& up = glm::vec3(Rinv_ * UP);

    const glm::vec2& nearSize = computePlaneSize(FOVY, NEAR_PLANE, getAspectRatio());
    const glm::vec3 nc = cameraPos + dir * NEAR_PLANE;
    const glm::vec3& a = up * nearSize.y;
    const glm::vec3& b = right * nearSize.x;
    const glm::vec3 ntl = nc + (a / 2.0f) - (b / 2.0f);
    const glm::vec3 ntr = ntl + b;
    const glm::vec3 nbl = ntl - a;
    const glm::vec3 nbr = nbl + b;

    const glm::vec2& farSize = computePlaneSize(FOVY, FAR_PLANE, getAspectRatio());
    const glm::vec3 fc = cameraPos + dir * FAR_PLANE;
    const glm::vec3& c = up * farSize.y;
    const glm::vec3& d = right * farSize.x;
    const glm::vec3 ftl = fc + (c / 2.0f) - (d / 2.0f);
    const glm::vec3 ftr = ftl + d;
    const glm::vec3 fbl = ftl - c;
    const glm::vec3 fbr = fbl + d;

    // Order may seem strange, but I use the most distant vectors
    // to define planes.  This way I believe the greatest accuracy
    // possible is achieved.
    CameraFrustum *const frustum = new CameraFrustum();
    frustum->planes_[0] = Plane(ftr, fbr, ntr);  // Right plane
    frustum->planes_[1] = Plane(fbl, ftl, nbl);  // Left plane
    frustum->planes_[2] = Plane(ftl, ftr, ntl);  // Top plane
    frustum->planes_[3] = Plane(fbr, fbl, nbr);  // Bottom plane
    frustum->planes_[4] = Plane(nbr, nbl, ntr);  // Near plane
    frustum->planes_[5] = Plane(fbr, ftr, fbl);  // Far plane
    
    return frustum;
}


// ========================
// Private
// ========================

void Camera::addToRotation(const float rx, const float ry, const float rz)
{
    static const glm::mat4 I(1);
    static const glm::vec3 vx = glm::vec3(1, 0, 0);
    static const glm::vec3 vy = glm::vec3(0, 1, 0);
    static const glm::vec3 vz = glm::vec3(0, 0, 1);

    rotation_[0] += rx;
    rotation_[1] += ry;
    rotation_[2] += rz;

    R_  = (rotation_[0] ? glm::rotate(rotation_[0], vx) : I) *
          (rotation_[1] ? glm::rotate(rotation_[1], vy) : I) *
          (rotation_[2] ? glm::rotate(rotation_[2], vz) : I);
    Rinv_ = glm::transpose(R_);
}


float Camera::getAspectRatio() const
{
    return static_cast<float>(viewportSize_.x) / viewportSize_.y;
}


glm::vec4 Camera::getVelocity(const unsigned dir) const
{
    switch (dir)
    {
    case 0: return glm::vec4( speed_,       0,       0, 0); break;
    case 1: return glm::vec4(-speed_,       0,       0, 0); break;
    case 2: return glm::vec4(      0,  speed_,       0, 0); break;
    case 3: return glm::vec4(      0, -speed_,       0, 0); break;
    case 4: return glm::vec4(      0,       0,  speed_, 0); break;
    case 5: return glm::vec4(      0,       0, -speed_, 0); break;
    }
    return glm::vec4(0.0f);
}


void Camera::updateViewMatrix()
{
    // TODO
    // view_ = glm::mat4(R_);
    // view_[3] = -position_;
    view_ = R_ * glm::translate(glm::vec3(-position_));
}
