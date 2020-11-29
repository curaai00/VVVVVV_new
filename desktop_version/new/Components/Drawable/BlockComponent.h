#pragma once

#include "../DrawableComponent.h"
#include <set>
#include <utility>

#define SURFACE_ARR_SIZE 1200
using Cells = std::array<ushort, SURFACE_ARR_SIZE>;

struct BlockIndex
{
    SDL_Point pos;
    ushort type;
};

// TODO: Optimize screen region for only use
class BlockComponent : public FullScreenComponent
{
public:
    BlockComponent(const Cells &cells, TileAsset &block_tile,
                   const std::set<ushort> &targets)
        : FullScreenComponent()
        , _target_types(targets)
    {
        auto contain = [](const std::set<ushort> &indicies, ushort var) -> bool {
            return indicies.find(var) != indicies.end();
        };

        auto size = block_tile.tilesize();
        int rows = 240 / size.y;
        int cols = 320 / size.x;

        // _draw_rect = SDL_Rect{320, 240, 0, 0};
        SDL_Rect rect{0, 0, size.x, size.y};
        for (int y = 0; y < rows; y++, rect.y += size.x, rect.x = 0)
        {
            for (int x = 0; x < cols; x++, rect.x += size.x)
            {
                auto var = cells[y * cols + x];
                if (contain(targets, var))
                {
                    util::sdl::blit(block_tile.tile(var), NULL, surface(), &rect);
                    _block_indices.push_back({SDL_Point{x, y}, var});
                }
            }
        }
    }

    void update(void) override { return; }

protected:
    std::vector<BlockIndex> _block_indices;
    std::set<ushort> _target_types;
};

class WallComponent : public BlockComponent
{
public:
    WallComponent(const Cells &blocks, TileAsset &block_tile)
        : BlockComponent(blocks, block_tile,
                         {83, 124, 125, 163, 164, 165, 203, 205, 244})
    {
    }
};

class ThornComponent : public BlockComponent
{
public:
    ThornComponent(const Cells &blocks, TileAsset &block_tile)
        : BlockComponent(blocks, block_tile, {6})
    {
    }
};
class BackWallComponent : public BlockComponent
{
public:
    BackWallComponent(const Cells &blocks, TileAsset &block_tile)
        : BlockComponent(blocks, block_tile, {680})
    {
    }
};