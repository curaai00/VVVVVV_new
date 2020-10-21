#pragma once

#include <SDL.h>
#include <algorithm>
#include <cmath>
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

    // get function pointer of update function to enforce update method
    void update(A p)
    {
        for (auto element : _elements)
            (element->*_update_func)(p);
    }
    Compositor &add(T *element)
    {
        _elements.push_back(element);
        return *this;
    }
    Compositor &rm(T *element)
    {
        auto res = std::find(_elements.begin(), _elements.end(), element);
        if (res != _elements.end()) _elements.erase(res);
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
    Compositor &add(T *element)
    {
        _elements.push_back(element);
        return *this;
    }
    Compositor &rm(T *element)
    {
        auto res = std::find(_elements.begin(), _elements.end(), element);
        if (res != _elements.end()) _elements.erase(res);
    }

    const std::vector<T *> &elements(void) { return _elements; }

protected:
    std::vector<T *> _elements;

private:
    void (T::*_update_func)();
};
// template <class T>
// void Compositor<T, void, void (T::*f)(void)>::update()
// {
//     for (auto element : _elements)
//         (element->*f)();
// }

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

// template <>
// class Compositor<class T, void, void (T::*f)(void)>
// {
// public:
//     Compositor &operator=(const Compositor &) = delete;

//     // get function pointer of update function to enforce update method
//     void update()
//     {
//         for (auto element : _elements)
//             (element->*f)();
//     }
//     Compositor &add(T *element)
//     {
//         _elements.push_back(element);
//         return *this;
//     }
//     Compositor &rm(T *element)
//     {
//         auto res = std::find(_elements.begin(), _elements.end(), element);
//         if (res != _elements.end()) _elements.erase(res);
//     }

//     const std::vector<T *> &elements(void) { return _elements; }

// protected:
//     std::vector<T *> _elements;
// };
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

namespace str
{
bool endsWith(const std::string &str, const std::string &suffix);
int len(std::string &str);

}; // namespace str

namespace sdl
{
SDL_Surface *CreateSurface(const SDL_Point &rect);

void blit(SDL_Surface *src, const SDL_Rect *src_r, SDL_Surface *dst,
          const SDL_Rect *dst_r);
SDL_Surface *patch(SDL_Surface *src, const SDL_Rect *rect);

Uint32 ReadPixel(const SDL_Surface *_surface, int x, int y);
void DrawPixel(SDL_Surface *_surface, int x, int y, Uint32 pixel);

SDL_Color uint2color(const SDL_Surface *surface, const Uint32 &c);
Uint32 color2uint(const SDL_Surface *surface, const SDL_Color &c);

void BlitSurfaceColoured(SDL_Surface *surface, const SDL_Color &c);

bool cmpColor(const SDL_Color &a, const SDL_Color &b);
bool cmpPos(const SDL_Point &a, const SDL_Point &b);
bool cmpRect(const SDL_Rect &a, const SDL_Rect &b);

SDL_Rect getTightRect(const SDL_Surface *surface);

}; // namespace sdl

namespace math
{
inline float fRandom() { return float(rand()) / float(RAND_MAX); }
inline int clamp(int x, int a, int b)
{
    if (x < a) x = a;
    if (b < x) x = b;
    return x;
}
}; // namespace math

}; // namespace util
