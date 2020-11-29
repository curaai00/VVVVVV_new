#pragma once
#include <vector>

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