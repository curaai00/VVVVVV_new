#pragma once

#include <SDL.h>
#include <json.hpp>

#include <stdlib.h>

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
    PNGAsset(const char* relative_asset_path)
        : Asset(relative_asset_path)
    {
        load();
    }
    inline virtual ~PNGAsset() { SDL_FreeSurface(asset); }

protected:
    virtual void _load(unsigned char* fileIn, size_t length) override;

public:
    SDL_Surface* asset;
};

class JsonAsset : public Asset
{
public:
    JsonAsset(const char* relative_asset_path)
        : Asset(relative_asset_path)
    {
        load(true);
    }
    virtual ~JsonAsset();

protected:
    virtual void _load(unsigned char* fileIn, size_t length) override;

public:
    nlohmann::json asset;
};