#pragma once

namespace util
{
namespace func
{
template <typename S, typename T>
void erase_if(S &container, T first, T last, std::function<bool(T)> checker)
{
    while (first != last)
    {
        if (checker(first))
        {
            first = container.erase(first);
        }
        else
            first++;
    }
}

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