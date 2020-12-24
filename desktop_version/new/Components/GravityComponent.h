#pragma once

#include "../Layer.h"
#include "../utils/func.h"
#include "Component.h"
#include <functional>
#include <unordered_set>

inline bool operator!=(SDL_Point const &a, SDL_Point const &b) { return !(a == b); }

enum class EGravityOrientation
{
    NATURELY,
    REVERSED
};

enum CollisionFlag : unsigned char
{
    UP = 0b0001,
    DOWN = 0b0010,
    LEFT = 0b0100,
    RIGHT = 0b1000
};

// TODO: only consturcted game and layer use friend after
// TODO: Legacy collision checker
class CollisionComponent : public Component
{
public:
    CollisionComponent(SDL_Surface *world, const Drawable *target)
        : Component()
        , world(world)
        , target(target)
    {
    }
    void update(void) override
    {
        using namespace std;

        auto boundary =
            extended_boundary(target->surface, speed); // speed -> move step
        auto check_collision = [&](const set<SDL_Point> &points) -> bool {
            SDL_Point top_left{target->rect.x, target->rect.y};

            auto is_valid = [&](const SDL_Surface *surface, SDL_Point p) -> bool {
                return util::sdl::getPixel(surface, p.x, p.y) != 0;
            };

            auto add = [&](SDL_Point pt) -> SDL_Point { return pt + top_left; };
            auto filter = [&](SDL_Point pt) -> bool { return is_valid(world, pt); };

            for (auto pt : points)
            {
                if (filter(add(pt)))
                {
                    return true;
                }
            }

            return false;
        };

        _is_collisioned = 0;
        auto assign = [&](CollisionFlag f,
                          const std::set<SDL_Point> &pts) -> unsigned char {
            return check_collision(pts) ? f : 0;
        };

        _is_collisioned |= assign(CollisionFlag::UP, boundary.up);
        _is_collisioned |= assign(CollisionFlag::DOWN, boundary.down);
        // _is_collisioned |= assign(CollisionFlag::LEFT, boundary.left);
        // _is_collisioned |= assign(CollisionFlag::RIGHT, boundary.right);
    }
    void set_speed(unsigned int speed) { this->speed = speed; }
    unsigned int get_speed(void) { return speed; }
    unsigned char is_collisioned(void) const { return _is_collisioned; }

protected:
    struct BoundaryPoints
    {
        std::set<SDL_Point> up;
        std::set<SDL_Point> down;
        std::set<SDL_Point> left;
        std::set<SDL_Point> right;
    };

    BoundaryPoints extended_boundary(const SDL_Surface *surface, int margin)
    {
        using namespace std;

        using x_fp = function<int(int, const vector<int> &)>;
        using y_fp = function<int(const vector<int> &, int)>;
        using intv = const vector<int> &;
        using points = set<SDL_Point>;
        using pts_iter = points::iterator;

        BoundaryPoints res;
        auto generate_default_boundary = [&surface](void) -> points {
            auto cols = util::range(0, surface->w);
            auto rows = util::range(0, surface->h);
            auto r_cols = util::func::reverse(cols);
            auto r_rows = util::func::reverse(rows);

            auto is_valid = [&](SDL_Point p) -> bool {
                return util::sdl::getPixel(surface, p.x, p.y) != 0;
            };

            x_fp check_col = [&](int x, const vector<int> &ys) -> int {
                for (auto y : ys)
                    if (is_valid({x, y})) return y;
                return -1;
            };
            y_fp check_row = [&](const vector<int> &xs, int y) -> int {
                for (auto x : xs)
                    if (is_valid({x, y})) return x;
                return -1;
            };
            points target;
            for (auto _rows : {rows, r_rows})
                for (auto col : cols)
                    target.insert(SDL_Point{col, check_col(col, _rows)});

            for (auto _cols : {cols, r_cols})
                for (auto row : rows)
                    target.insert(SDL_Point{row, check_row(_cols, row)});

            return target;
        };
        auto added = [](points pts, SDL_Point margin) -> points {
            points res;
            for (auto x : pts)
                res.insert(x + margin);
            return res;
        };

        auto _default = generate_default_boundary();

        // TODO: This can dangerous for when exists space between user and something?
        res.up = added(_default, SDL_Point{0, -margin});
        res.down = added(_default, SDL_Point{0, margin});
        res.left = added(_default, SDL_Point{-margin, 0});
        res.right = added(_default, SDL_Point{margin, 0});

        return res;
    };

protected:
    SDL_Surface *world;
    const Drawable *target;

    EGravityOrientation ori;
    unsigned char _is_collisioned = 0;
    int speed = 1;
};

class GravityComponent : public Component
{
public:
    GravityComponent(Drawable *pos, CollisionComponent *collision_checker,
                     const EGravityOrientation &orientation)
        : Component()
        , collision_checker(collision_checker)
        , pos(pos)
        , orientation(orientation)
    {
        collision_checker->set_speed(speed);
    }

    void update(void) override
    {
        // TODO: can be dangerous for when horizontal & vertical speed can be
        // different
        if (collision_checker->get_speed() != speed)
        {
            collision_checker->set_speed(speed);
            collision_checker->update();
        }

        auto collision = collision_checker->is_collisioned();
        auto can_update = ~collision & (orientation == EGravityOrientation::NATURELY
                                            ? CollisionFlag::DOWN
                                            : CollisionFlag::UP);
        if (can_update)
            pos->rect.y +=
                orientation == EGravityOrientation::NATURELY ? speed : -speed;
    }

protected:
    CollisionComponent *collision_checker;
    Drawable *pos;
    const EGravityOrientation &orientation;
    int speed = 3; // TODO: collision_checker's speed when own speed changed
};
