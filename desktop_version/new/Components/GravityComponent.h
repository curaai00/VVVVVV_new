#pragma once

#include "../Layer.h"
#include "../utils/func.h"
#include "Component.h"
#include <unordered_set>

inline SDL_Point operator+(SDL_Point const &a, SDL_Point const &b)
{
    return {a.x + b.x, a.y + b.y};
    // return a.x == b.x && a.y == b.y;
}
inline bool operator==(SDL_Point const &a, SDL_Point const &b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(SDL_Point const &a, SDL_Point const &b) { return !(a == b); }

enum class EGravityOrientation
{
    NATURELY,
    REVERSED
};

class CollisionComponent : public Component
{
public:
    CollisionComponent(Layer *layer, Drawable &drawable)
        : Component()
        , layer(layer)
        , target(drawable)
    {
    }
    void update(void) override
    {
        _is_collisioned = util::sdl::collision_check(layer->surface(), target);
    }
    const bool &get_collision_checker(void) { return _is_collisioned; }

    friend class GravityComponent;

protected:
    Layer *layer = nullptr;
    Drawable &target;

    bool _is_collisioned = false;
};

// TODO: only consturcted game and layer use friend after
// TODO: Legacy collision checker
class GravityComponent : public Component
{
public:
    GravityComponent(SDL_Rect &pos, CollisionComponent *collision_checker,
                     EGravityOrientation ori = EGravityOrientation::NATURELY)
        : Component()
        , collision_checker(collision_checker)
        , pos(pos)
        , ori(ori)
    {
    }
    void update(void) override
    {
        auto is_valid = [](const SDL_Surface *surface, SDL_Point p) -> bool {
            return util::sdl::getPixel(surface, p.x, p.y) != 0;
        };

        auto get_boundary =
            [&is_valid](
                const Drawable &drawble,
                const std::vector<SDL_Point> &filter) -> std::vector<SDL_Point> {
            const SDL_Surface *surface = drawble.surface;
            SDL_Rect rect = drawble.rect;

            auto contain = [](const std::vector<SDL_Point> &v,
                              SDL_Point var) -> bool {
                return std::find(v.begin(), v.end(), var) != v.end();
            };

            auto check_row = [&](const std::vector<int> &range, const int y) -> int {
                for (auto x : range)
                    if (is_valid(surface, {x, y})) return x;
                return -1;
            };
            auto check_col = [&](const std::vector<int> &range, const int x) -> int {
                for (auto y : range)
                    if (is_valid(surface, {x, y})) return y;
                return -1;
            };

            auto cols = util::range(0, surface->w);
            auto r_cols = util::func::reverse(cols);
            auto rows = util::range(0, surface->h);
            auto r_rows = util::func::reverse(rows);
            SDL_Point top_left{rect.x, rect.y};
            std::vector<SDL_Point> target;
            for (auto _rows : {rows, r_rows})
            {
                for (auto col : cols)
                {
                    auto pt = SDL_Point{col, check_col(_rows, col)} + top_left;
                    if (!contain(filter, pt)) target.push_back(pt);
                }
            }

            for (auto _cols : {cols, r_cols})
            {
                for (auto row : rows)
                {
                    auto pt = SDL_Point{row, check_row(_cols, row)} + top_left;
                    if (!contain(filter, pt)) target.push_back(pt);
                }
            }

            return target;
        };

        // return false;
        auto moved = ori == EGravityOrientation::NATURELY ? speed : -speed;

        auto original = get_boundary(collision_checker->target, {});
        auto shifted_obj = collision_checker->target;
        shifted_obj.rect.y += moved;
        auto check_list = get_boundary(shifted_obj, original);

        auto add = [](SDL_Point a, SDL_Point b) -> SDL_Point {
            return {a.x + b.x, a.y + b.y};
        };

        SDL_SaveBMP(collision_checker->layer->surface(), "check_collision.bmp");
        bool conflicted = false;
        for (auto t : check_list)
            if (is_valid(collision_checker->layer->surface(), t)) conflicted = true;

        if (!conflicted)
        {
            pos.y += moved;
        }
    }
    EGravityOrientation &get_gravity(void) { return ori; }

protected:
    CollisionComponent *collision_checker;
    SDL_Rect &pos;
    EGravityOrientation ori;
    int speed = 1;
};