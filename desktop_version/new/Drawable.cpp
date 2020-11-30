#include "Drawable.h"
#include "utils/sdl.h"

Drawable &Drawable::operator=(Drawable const &another)
{
    surface = util::sdl::copy(another.surface);
    rect = another.rect;
    return *this;
}