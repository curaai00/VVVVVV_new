#include "Background.h"
#include "util.h"

#include <tuple>

IntroBackground::IntroBackground()
    : ScreenDrawable()
{}
IntroBackground::~IntroBackground() {}

void IntroBackground::update(void)
{
    stripe.update();

    SDL_BlitSurface(stripe.surface(), NULL, _surface, NULL);
}

SpaceBackground::SpaceBackground()
    : ScreenDrawable()
{}

SpaceBackground::~SpaceBackground() {}

void SpaceBackground ::update(void)
{
    space.update();

    SDL_BlitSurface(space.surface(), NULL, _surface, NULL);
}