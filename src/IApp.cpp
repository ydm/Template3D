#include "IApp.hpp"
#include <iostream>


// ========================
// IApp
// ========================

IApp::IApp()
{
}


IApp::~IApp()
{
}


bool IApp::init()
{
    return true;
}


void IApp::terminate()
{
}


// ========================
// Callbacks
// ========================

void IApp::onChar(const unsigned int codepoint)
{
}


void IApp::onCursorPosition(const double xpos, const double ypos)
{
}


void IApp::onKey(const int key, const int scancode, const int action, const int mods)
{
}


void IApp::onMouseButton(int button, int action, int mods)
{
}


void IApp::onResize(const int width, const int height)
{
}


void IApp::onScroll(const double xoffset, const double yoffset)
{
}


// ========================
// Draw routine
// ========================

void IApp::draw()
{
}
