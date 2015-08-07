#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "CameraFrustum.hpp"


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
     * Update camera's position by walk()ing in
     * directions specified.
     */
	bool update(const float dt);

    // Walk
    void walk(const enum Direction dir);
    void stopWalking(const enum Direction dir);

    // Mouse controls
    void enableMouse(const int x, const int y);
    void mouseMotion(const int x, const int y);
    void disableMouse();

    // Manually set camera state.
    void rotate(const float rx, const float ry, const float rz);
    void rotateDeg(const float rx, const float ry, const float rz);
    void setPosition(const glm::vec3& pos);

    // Parameters
    float getMovementSpeed() const;
    void setMovementSpeed(const float speed);
    void setViewportSize(const int w, const int h);

    // Ray functions
	glm::vec3 getLookDirection() const;
	glm::vec3 getMouseRay(const int x, const int y) const;
    const glm::vec4& getPosition() const;

    // Matrix getters
    const glm::mat4& getViewMatrix() const;
	/**
	 * Get current projection matrix.  Since projection
     * depends on viewport size, make sure it's set first.
	 */
    const glm::mat4& getProjectionMatrix() const;

    // Visibility checking
    /**
     * Clients are responsible for freeing the object.
     */
    CameraFrustum *getCameraFrustum() const;
    
private:
    float getAspectRatio() const;
    glm::vec4 getVelocity(const unsigned dir);
    void updateViewMatrix();

    bool directions_[6];
	glm::ivec2 mousePosition_;
    glm::vec4 position_; // Eye/camera position
	glm::mat4 projection_;
    glm::mat4 R_;
    glm::mat4 Rinv_;
    glm::vec3 rotation_;
    float speed_;
    glm::vec4 velocity_;
    glm::mat4 view_;
    glm::ivec2 viewportSize_;
};


#endif // __CAMERA_HPP__
