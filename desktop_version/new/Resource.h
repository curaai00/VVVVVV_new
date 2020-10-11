#pragma once

#include "util.h"

#include <json.hpp>

#include <map>
#include <stdlib.h>

#define SURFACE_ARR_SIZE 1200

class Resource
{
public:
    static void load2Mem(const char* name,
                         unsigned char** mem,
                         size_t* len,
                         bool addnull = false);
};

class Asset
{
public:
    Asset(const char* relative_asset_path);
    virtual ~Asset();

protected:
    void load(bool addnull = false);
    virtual void _load(unsigned char* fileIn, size_t length) = 0;
    const char* asset_path;
};

class PNGAsset : public Asset
{
public:
    PNGAsset(const char* relative_asset_path);
    virtual ~PNGAsset();

protected:
    virtual void _load(unsigned char* fileIn, size_t length) override;

public:
    SDL_Surface* asset;

private:
    unsigned char* _asset_ptr;
};

class JsonAsset : public Asset
{
public:
    JsonAsset(const char* relative_asset_path);
    virtual ~JsonAsset();

protected:
    virtual void _load(unsigned char* fileIn, size_t length) override;

public:
    nlohmann::json asset;
};

class FontAsset : public Asset
{
public:
    FontAsset(const char* relative_asset_path);
    virtual ~FontAsset();

protected:
    virtual void _load(unsigned char* fileIn, size_t length) override;

public:
    int getFontIdx(uint32_t ch);
    static int getFontLen(uint32_t ch);

    std::map<int, int> font_positions;
};

class TileAsset : public PNGAsset
{
public:
    TileAsset(const char* relatvie_asset_path, SDL_Point size);
    virtual ~TileAsset();

    SDL_Surface* tile(unsigned int i) const;
    size_t tilecount(void) const { return tiles.size(); }
    SDL_Point tilesize(void) const { return _size; }

protected:
    virtual void _load(unsigned char* fileIn, size_t length) override;

private:
    inline SDL_Surface* GetSubSurface(const SDL_Rect& area)
    {
        // we will slow things down.
        SDL_Surface* preSurface =util::sdl::CreateSurface({area.w, area.h});
        SDL_BlitSurface(asset, &area, preSurface, NULL);
        return preSurface;
    }

private:
    std::vector<SDL_Surface*> tiles;
    SDL_Point _size;
};