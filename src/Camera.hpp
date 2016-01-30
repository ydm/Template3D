#ifndef __T3D_CAMERA_HPP__
#define __T3D_CAMERA_HPP__

#include "CameraFrustum.hpp"


namespace t3d
{

/**
 *
 */
class Camera
{
public:
    enum Direction {
        RIGHT,    LEFT,     // x
        UP,       DOWN,     // y
        BACKWARD, FORWARD   // z
    };

    Camera(void);
    virtual ~Camera(void);

    /**
     * Update camera's position by walking in directions specified with walk()
     * and stopWalking() and looking in the direction adjusted with
     * enableMouse() -- mouseMotion() -- disableMouse().
     */
    bool update(const float dt);

    // --------------
    // Walking around
    // --------------
    void walk(const enum Direction dir);
    void stopWalking(const enum Direction dir);

    // --------------
    // Mouse controls
    // --------------
    void enableMouse();
    void mouseMotion(const int x, const int y);
    void disableMouse();

    // -------------------------
    // Manually set camera state
    // -------------------------
    void setPosition(const glm::vec3& pos);
    // TODO: rotation

    // ----------
    // Parameters
    // ----------
    float getMovementSpeed() const;
    void setMovementSpeed(const float speed);
    void setViewportSize(const int w, const int h);

    // --------------------
    // Ray function getters
    // --------------------
    glm::vec3 getLookDirection() const;
    // TODO: Return t3d::Ray!
    glm::vec3 getMouseRay(const double x, const double y) const;
    glm::vec3 getMouseRay(const float x, const float y) const;
    const glm::vec4& getPosition() const;

    // --------------
    // Matrix getters
    // --------------
    const glm::mat4& getViewMatrix() const;
    /**
     * Get current projection matrix.  Since projection
     * depends on viewport size, make sure it's set first.
     */
    const glm::mat4& getProjectionMatrix() const;
    /**
     * Useful for visibility checks.  Clients are responsible for freeing the
     * object.
     */
    CameraFrustum *getCameraFrustum() const;

private:
    void addToRotation(const float rx, const float ry, const float rz);
    float getAspectRatio() const;
    glm::vec4 getVelocity(const unsigned dir) const;
    void updateViewMatrix();

    bool directions_[6];
    bool mouseEnabled_;
    glm::ivec2 mousePosition_;
    glm::vec4 position_; // Camera position
    glm::mat4 projection_;
    glm::mat4 R_;
    glm::mat4 Rinv_;
    glm::vec3 rotation_;
    float speed_;
    glm::vec4 velocity_;
    glm::mat4 view_;
    glm::ivec2 viewportSize_;
};

} // namespace


#endif // __T3D_CAMERA_HPP__
