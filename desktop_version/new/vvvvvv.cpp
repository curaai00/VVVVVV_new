#include "vvvvvv.h"

VVVVVV::VVVVVV()
{
    map.setRoom({ 114, 105 });
    addScreenLayer(&spacebackground);
    addScreenLayer(&map);
}

VVVVVV::~VVVVVV() {}

void VVVVVV::update(void)
{
    spacebackground.update();
    map.update();
}