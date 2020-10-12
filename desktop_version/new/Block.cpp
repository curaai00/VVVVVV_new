#include "Block.h"
#include "util.h"

#include <algorithm>
#include <math.h>

bool Block::is_acrossed(const SDL_Point &point) const
{
    return util::sdl::ReadPixel(_surface, point.x, point.y) != 0;
}

void Block::construct(const std::array<unsigned short, SURFACE_ARR_SIZE> &room_arr, const TileAsset &tile_asset)
{
    auto temp_surface = util::sdl::CreateSurface(SDL_Point{320, 240});

    auto tile_size = tile_asset.tilesize();
    int rows = 240 / tile_size.y;
    int cols = 320 / tile_size.x;

    auto contain = [](const std::vector<unsigned short> &indicies, unsigned short var) -> bool {
        return std::find(indicies.begin(), indicies.end(), var) != indicies.end();
    };
    auto update_rect = [&tile_size](SDL_Rect &rect, SDL_Point pos) {
        rect.x = std::min(rect.x, pos.x);
        rect.y = std::min(rect.y, pos.y);
        rect.w = std::max(rect.w, pos.x + tile_size.x - rect.x);
        rect.h = std::max(rect.h, pos.y + tile_size.y - rect.y);
        // rect.h = std::max(rect.h, pos.y + (rect.y + 1) * tile_size.y);
    };

    _draw_rect = SDL_Rect{320, 240, 0, 0};
    SDL_Rect tilerect{0, 0, 8, 8};
    for (int y = 0; y < rows; y++)
    {
        tilerect.x = 0;
        for (int x = 0; x < cols; x++)
        {
            auto var = room_arr[y * cols + x];
            if (contain(_block_indicies, var))
            {
                update_rect(_draw_rect, SDL_Point{tilerect.x, tilerect.y});
                util::sdl::blit(tile_asset.tile(var), NULL, temp_surface, &tilerect);
                _block_tiles.push_back(SDL_Point{x, y});
            }
            tilerect.x += tile_size.x;
        }
        tilerect.y += tile_size.y;
    }

    _surface = util::sdl::patch(temp_surface, &_draw_rect);
    SDL_FreeSurface(temp_surface);
}