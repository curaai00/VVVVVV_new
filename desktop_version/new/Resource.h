#pragma once

#include <SDL.h>
#include <stdlib.h>

class Resource
{
public:
    static void load2Mem(const char* name,
                         unsigned char** mem,
                         size_t* len,
                         bool addnull = false);
};

struct PNGAsset
{
    PNGAsset(const char* relative_asset_path);
    ~PNGAsset();

    SDL_Surface* asset;
};