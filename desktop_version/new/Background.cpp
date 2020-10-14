#include "Background.h"
#include "util.h"

#include <tuple>

IntroBackground::IntroBackground()
    : Layer()
{
    addDrawable(&stripe);
}
IntroBackground::~IntroBackground() {}

void IntroBackground::update(void) { stripe.update(); }

SpaceBackground::SpaceBackground()
    : Layer()
{
    addDrawable(&space);
}

SpaceBackground::~SpaceBackground() {}

void SpaceBackground ::update(void) { space.update(); }