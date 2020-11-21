#pragma once

#include "util.h"

#include <string>
#include <utf8/unchecked.h>

namespace util
{
namespace str
{
inline int len(const std::string &str)
{
    int bfontpos = 0;
    auto iter = str.cbegin();
    while (iter != str.cend())
    {
        int cur = utf8::unchecked::next(iter);
        bfontpos += cur < 32 ? 6 : 8;
    }
    return bfontpos;
}

inline bool endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

}; // namespace str

} // namespace util
