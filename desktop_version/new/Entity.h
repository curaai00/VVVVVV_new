#pragma once

#include "Components/Component.h"
#include <vector>

using Entity = Compositor<Component, &Component::update>;