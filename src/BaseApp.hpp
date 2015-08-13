#ifndef __BASE_APP_HPP__
#define __BASE_APP_HPP__

#include "IApp.hpp"
#include <AntTweakBar.h>
#include "Camera.hpp"
#include "DrawableManager.hpp"


class BaseApp : public IApp
{
public:
    BaseApp();
    virtual ~BaseApp();

    virtual bool init() override;
    virtual void terminate() override;
    
    /**
     * Update routine.  Returns true on state change.
     */
    virtual bool update(const float dt);

    // Callbacks
    virtual void onChar(const unsigned int codepoint) override;
    virtual void onCursorPosition(const double xpos, const double ypos) override;
    virtual void onKey(const int key, const int scancode, const int action, const int mods) override;
    virtual void onMouseButton(int button, int action, int mods) override;
    virtual void onResize(const int width, const int height) override;
    virtual void onScroll(const double xoffset, const double yoffset) override;

    // Draw routine
    virtual void draw() override;

protected:
    Camera camera_;
    DrawableManager drawables_;
};

#endif // __BASE_APP_HPP__
