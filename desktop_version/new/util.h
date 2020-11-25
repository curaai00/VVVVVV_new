#pragma once

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <string>
#include <vector>

#ifndef SDL_BYTE_MASK
#define SDL_BYTE_MASK
const uint32_t R_MASK = 0x000000ff;
const uint32_t G_MASK = 0x0000ff00;
const uint32_t B_MASK = 0x00ff0000;
const uint32_t A_MASK = 0xff000000;
#endif

struct noncopyable
{
    noncopyable(){};
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
};

template <class T, typename A = void>
class Compositor
{
public:
    Compositor(void (T::*f)(A))
        : _update_func(f)
    {
    }
    Compositor(const std::vector<T *> &elements, void (T::*f)(A))
        : _elements(elements)
        , _update_func(f)
    {
    }
    Compositor(const Compositor &) = delete;
    Compositor &operator=(const Compositor &) = delete;

    ~Compositor()
    {
        for (auto elem : _elements)
            delete elem;
    }

    // get function pointer of update function to enforce update method
    void update(A p)
    {
        for (auto element : _elements)
            (element->*_update_func)(p);
    }
    void push(T *element) { _elements.push_back(element); }
    T *pop(T *element)
    {
        auto res = std::find(_elements.begin(), _elements.end(), element);
        if (res != _elements.end())
            _elements.erase(res);
        else
            std::invalid_argument("Can't remove element");
        return *res;
    }

    const std::vector<T *> &elements(void) { return _elements; }

protected:
    std::vector<T *> _elements;

private:
    void (T::*_update_func)(A);
};
template <class T>
class Compositor<T, void>
{
public:
    Compositor(void (T::*f)())
        : _update_func(f)
    {
    }
    Compositor(const std::vector<T *> &elements, void (T::*f)())
        : _elements(elements)
        , _update_func(f)
    {
    }
    Compositor(const Compositor &) = delete;
    Compositor &operator=(const Compositor &) = delete;

    // get function pointer of update function to enforce update method
    void update()
    {
        for (auto element : _elements)
            (element->*_update_func)();
    }

    void push(T *element) { _elements.push_back(element); }
    T *pop(T *element)
    {
        auto res = std::find(_elements.begin(), _elements.end(), element);
        if (res != _elements.end())
            _elements.erase(res);
        else
            std::invalid_argument("Can't remove element");
        return *res;
    }

    const std::vector<T *> &elements(void) { return _elements; }

protected:
    std::vector<T *> _elements;

private:
    void (T::*_update_func)();
};

class NotImplementedError : public std::logic_error
{
private:
    std::string _text;

    NotImplementedError(const char *message, const char *function)
        : std::logic_error("Not Implemented")
    {
        _text = message;
        _text += " : ";
        _text += function;
    }

public:
    NotImplementedError()
        : NotImplementedError("Not Implememented", __FUNCTION__)
    {
    }

    NotImplementedError(const char *message)
        : NotImplementedError(message, __FUNCTION__)
    {
    }

    inline virtual const char *what() const throw() { return _text.c_str(); }
};

namespace util
{
template <typename T>
std::vector<T> range(T N1, T N2)
{
    T small = N1 < N2 ? N1 : N2;
    T big = N1 < N2 ? N2 : N1;

    std::vector<T> numbers(big - small);
    std::iota(numbers.begin(), numbers.end(), small);

    if (big == N1) std::reverse(numbers.begin(), numbers.end());

    return numbers;
}
}; // namespace util
