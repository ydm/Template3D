#include "OrthographicApp.hpp"
#include <AntTweakBar.h>
#include "MandelbrotDrawable.hpp"


// TODO: CURRENTLY COUPLED WITH MANDELBROT!


namespace t3d
{

// ========================
// OrthographicApp
// ========================

OrthographicApp::OrthographicApp()
: center_(0.0f)
, drawables_()
, mandelbrot_(nullptr)
, zoom_(1.0f)
{
}


OrthographicApp::~OrthographicApp()
{
}


bool OrthographicApp::init()
{
    if (drawables_.init() == false) {
	return false;
    }
    mandelbrot_ = new MandelbrotDrawable();
    mandelbrot_->setUniformFloat("u_zoom", zoom_);
    mandelbrot_->setUniformVec2("u_center", glm::value_ptr(center_));

    drawables_.addDrawable(mandelbrot_);
    drawables_.setViewMatrix(glm::value_ptr(glm::mat4(1.0f)));
    return true;
}


void OrthographicApp::terminate()
{
    drawables_.terminate();
}


bool OrthographicApp::update(const float dt)
{
    return drawables_.update(dt);
}


// ========================
// Callbacks
// ========================

void OrthographicApp::onChar(const unsigned int codepoint)
{
}


void OrthographicApp::onCursorPosition(const double xpos, const double ypos)
{
	using namespace std;
	cout << "x=" << xpos << ", y=" << ypos << endl;
}


void OrthographicApp::onKey(const int key, const int scancode, const int action, const int mods)
{
	static const float STEP = 0.05f;
	switch (key)
	{
        case GLFW_KEY_UP:    center_.y -= STEP / zoom_; break;
        case GLFW_KEY_DOWN:  center_.y += STEP / zoom_; break;
        case GLFW_KEY_LEFT:  center_.x += STEP / zoom_; break;
        case GLFW_KEY_RIGHT: center_.x -= STEP / zoom_; break;
	default: return;
	}
	mandelbrot_->setUniformVec2("u_center", glm::value_ptr(center_));
}


void OrthographicApp::onMouseButton(int button, int action, int mods)
{
}


void OrthographicApp::onResize(const int width, const int height)
{
    // Fits height
    const float ratio = static_cast<float>(width) / height;
    const float half = ratio / 2.0f;
    // const float half = 0.5f;
    const glm::mat4& projection = glm::ortho(-half, half, -0.5f, 0.5f);
    drawables_.setProjectionMatrix(glm::value_ptr(projection));
}


void OrthographicApp::onScroll(const double xoffset, const double yoffset)
{
	static const float K = 1.1f;
	if (yoffset > 0.0)
	{
		zoom_ /= K;
		
	}
	else if (yoffset < 0.0)
	{
		zoom_ *= K;
	}
	mandelbrot_->setUniformFloat("u_zoom", zoom_);
}


// ========================
// Draw routine
// ========================

void OrthographicApp::draw()
{
    drawables_.draw();
}

} // namespace

