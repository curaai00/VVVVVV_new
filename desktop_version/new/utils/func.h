#pragma once

namespace util
{
namespace func
{

template <class T>
inline std::vector<T> reverse(const std::vector<T> &v)
{
    std::vector<T> res;
    res.resize(v.size());
    std::reverse_copy(v.begin(), v.end(), res.begin());
    return res;
}

}; // namespace func
}; // namespace util