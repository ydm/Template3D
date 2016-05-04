#ifndef __IAPP_HPP__
#define __IAPP_HPP__


namespace t3d
{

class IApp
{
public:
    IApp();
    virtual ~IApp();

    virtual bool init();
    virtual void terminate();

    // Callbacks
    virtual void onChar(const unsigned int codepoint);
    virtual void onCursorPosition(const double xpos, const double ypos);
    virtual void onKey(const int key, const int scancode, const int action, const int mods);
    virtual void onMouseButton(int button, int action, int mods);
    virtual void onResize(const int width, const int height);
    virtual void onScroll(const double xoffset, const double yoffset);

    // Draw routine
    virtual void draw();
};

} // namespace

#endif // __APP_HPP__
