#ifndef __APP_HPP__
#define __APP_HPP__

#include "IApp.hpp"
#include <GL/glew.h>
#include <AntTweakBar.h>


class App : public IApp
{
public:
    App();
    virtual ~App();

    virtual bool init() override;
    virtual void terminate() override;

    // Callbacks
    virtual void onChar(const unsigned int codepoint) override;
    virtual void onCursorPosition(const double xpos, const double ypos) override;
    virtual void onKey(const int key, const int scancode, const int action, const int mods) override;
    virtual void onMouseButton(int button, int action, int mods) override;
    virtual void onResize(const int width, const int height) override;
    virtual void onScroll(const double xoffset, const double yoffset) override;

    // Draw routine
    virtual void draw() override;

private:
    double speed_;
    TwBar *twbar_;
    GLuint vao_;
};

#endif // __APP_HPP__
