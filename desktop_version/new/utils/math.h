#pragma once

#include "util.h"

#include <cmath>

namespace util
{
namespace math
{
inline float fRandom() { return float(rand()) / float(RAND_MAX); }

inline int clamp(int x, int a, int b)
{
    if (x < a) x = a;
    if (b < x) x = b;
    return x;
}

} // namespace math

}; // namespace util