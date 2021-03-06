#pragma once

#include "util.h"
#include "utils/sdl.h"
#include "utils/str.h"

#include <json.hpp>

#include <map>
#include <stdlib.h>

#define SURFACE_ARR_SIZE 1200

class Resource
{
public:
    static void load2Mem(const char *name, unsigned char **mem, size_t *len,
                         bool addnull = false);
};

class Asset
{
public:
    Asset(const char *relative_asset_path);
    virtual ~Asset();

protected:
    void load(bool addnull = false);
    virtual void _load(unsigned char *fileIn, size_t length) = 0;
    const char *asset_path;
};

class PNGAsset : public Asset
{
public:
    PNGAsset(const char *relative_asset_path);
    virtual ~PNGAsset();

protected:
    virtual void _load(unsigned char *fileIn, size_t length) override;

public:
    SDL_Surface *asset;

private:
    unsigned char *_asset_ptr;
};

class JsonAsset : public Asset
{
public:
    JsonAsset(const char *relative_asset_path);
    virtual ~JsonAsset();

protected:
    virtual void _load(unsigned char *fileIn, size_t length) override;

public:
    nlohmann::json asset;
};

class FontAsset : public Asset
{
public:
    FontAsset(const char *relative_asset_path);
    virtual ~FontAsset();

protected:
    virtual void _load(unsigned char *fileIn, size_t length) override;

public:
    int getFontIdx(uint32_t ch);
    static int getFontLen(uint32_t ch);

    std::map<int, int> font_positions;
};

class TileAsset : public PNGAsset
{
public:
    TileAsset(const char *relatvie_asset_path, SDL_Point size);
    virtual ~TileAsset();
    TileAsset(const TileAsset &tileasset);
    TileAsset &operator=(TileAsset const &tileasset);

    SDL_Surface *tile(unsigned int i);
    size_t tilecount(void) const { return tiles.size(); }
    SDL_Point tilesize(void) const { return _size; }

protected:
    virtual void _load(unsigned char *fileIn, size_t length) override;

    std::vector<SDL_Surface *> tiles;
    SDL_Point _size;
};