#include "vvvvvv.h"

VVVVVV::VVVVVV()
{
    addScreenLayer(&spacebackground);
    addScreenLayer(&map);
}

VVVVVV::~VVVVVV() {}

void VVVVVV::update(void)
{
    spacebackground.update();
    map.update();
}