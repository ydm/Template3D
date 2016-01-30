#ifndef __T3D_DRAWABLE_MANAGER_HPP__
#define __T3D_DRAWABLE_MANAGER_HPP__

#include "Drawable.hpp"


namespace t3d
{

/**
 * Usage:
 * 1. Create an instance
 * 2. init()
 * 3. Add/remove drawables and draw()
 * 4. terminate()
 * 5. Delete instance
 */
class DrawableManager
{
public:
    DrawableManager();
    ~DrawableManager();

    bool init();
    void terminate();

    /**
     * Add a drawable to be managed by this DrawableManager.
     *
     * Drawable's life cycle will be executed as follows:
     * init() -> draw() -> terminate() -> delete
     */
    void addDrawable(Drawable *const drawable);
    void draw();
    bool update(const float dt);

    void setProjectionMatrix(const GLfloat *const M);
    void setViewMatrix(const GLfloat *const M);

private:
    Drawable *head_;
    Drawable *tail_;
};

} // namespace

#endif // __T3D_DRAWABLE_MANAGER_HPP__
