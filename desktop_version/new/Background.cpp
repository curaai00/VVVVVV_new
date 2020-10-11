#include "Background.h"
#include "util.h"

#include <tuple>

IntroBackground::IntroBackground()
: Layer(Type::DYNAMIC)
{
    addDrawable(&stripe);
}
IntroBackground::~IntroBackground() {}

void IntroBackground::update(void)
{
    stripe.update();
}

SpaceBackground::SpaceBackground()
: Layer(Type::DYNAMIC)
{
    addDrawable(&space);
}

SpaceBackground::~SpaceBackground() {}

void SpaceBackground ::update(void)
{
    space.update();
}