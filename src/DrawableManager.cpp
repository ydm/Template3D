#include "DrawableManager.hpp"
#include <iostream>


DrawableManager::DrawableManager()
: head_(nullptr)
, tail_(nullptr)
{
}


DrawableManager::~DrawableManager()
{
}


bool DrawableManager::init()
{
    return true;
}


void DrawableManager::terminate()
{
    Drawable *d = head_;
	
    while (d != nullptr)
    {
	d->terminate();
		
	Drawable *const del = d;
	d = d->next_;

	delete del;
    }

    head_ = tail_ = nullptr;
}


void DrawableManager::addDrawable(Drawable *const drawable)
{
	if (!drawable->init())
	{
		std::cerr << "[E] DrawableManager::addDrawable: Failed to initialize drawable" << std::endl;
		return;
	}

	if (head_ == nullptr)
	{
		head_ = tail_ = drawable;
	}
	else
	{
		tail_->next_ = drawable;
		tail_ = drawable;
	}
}


void DrawableManager::draw()
{
	for (Drawable *d = head_; d != nullptr; d = d->next_)
	{
		d->draw();
	}
}


bool DrawableManager::update(const float dt)
{
	bool res = false;
	for (Drawable *d = head_; d != nullptr; d = d->next_)
	{
		if (d->update(dt))
		{
			res = true;
		}
	}
	return res;
}


void DrawableManager::setProjectionMatrix(const GLfloat *const M)
{
	for (Drawable *d = head_; d != nullptr; d = d->next_)
	{
		d->setProjectionMatrix(M);
	}
}


void DrawableManager::setViewMatrix(const GLfloat *const M)
{
	for (Drawable *d = head_; d != nullptr; d = d->next_)
	{
		d->setViewMatrix(M);
	}
}
