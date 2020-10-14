#pragma once

#include "Components/GraphicComponents.h"
#include "Layer.h"
#include "Resource.h"
#include "util.h"

#include <SDL.h>

#include <array>
#include <vector>

// Add StripeComponent
class IntroBackground : public Layer
{
public:
    IntroBackground();
    virtual ~IntroBackground();

    void update(void) override;

    StripeComponent stripe;
};

// Add StarComponent
class SpaceBackground : public Layer
{
public:
    SpaceBackground();
    virtual ~SpaceBackground();

    void update(void) override;

private:
    SpaceComponent space;
};