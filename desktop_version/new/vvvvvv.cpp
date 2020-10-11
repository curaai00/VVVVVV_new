#include "vvvvvv.h"

VVVVVV::VVVVVV()
{
    addLayer(&spacebackground);
    addLayer(map.setRoom({ 114, 105 }));
}

VVVVVV::~VVVVVV() {}

void VVVVVV::update(void)
{
    spacebackground.update();
}