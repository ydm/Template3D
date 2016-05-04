#include "DrawableManager.hpp"


namespace t3d
{

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
        Drawable *const n = d->next_;

        d->terminate();
        delete d;

        d = n;
    }

    head_ = tail_ = nullptr;
}


void DrawableManager::addDrawable(Drawable *const drawable)
{
    if (!drawable->init())
    {
        // log::e << "" << log::endl;
        // TODO
        std::cerr << "[E] DrawableManager::addDrawable: Failed to initialize drawable" << std::endl;
        return;
    }

    if (head_ == nullptr)
    {
        head_ = tail_ = drawable;
    }
    else
    {
        assert(drawable->next_ == nullptr);
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

} // namespace
