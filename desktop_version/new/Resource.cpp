#include "Resource.h"
#include "util.h"

#include <exception>
#include <physfs.h>
#include <tinyxml2.h>
#include <utf8/unchecked.h>

// clang-format off
#if defined(_WIN32)
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
// clang-format on

#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) ||      \
    defined(__OpenBSD__) || defined(__HAIKU__) || defined(__DragonFly__)
#include <dirent.h>
#include <limits.h>
#include <spawn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_PATH PATH_MAX
#endif

extern "C"
{
    extern unsigned lodepng_decode24(unsigned char** out,
                                     unsigned* w,
                                     unsigned* h,
                                     const unsigned char* in,
                                     size_t insize);
    extern unsigned lodepng_decode32(unsigned char** out,
                                     unsigned* w,
                                     unsigned* h,
                                     const unsigned char* in,
                                     size_t insize);
}

void Resource::load2Mem(const char* name,
                        unsigned char** mem,
                        size_t* len,
                        bool addnull)
{
    PHYSFS_File* handle = PHYSFS_openRead(name);
    if (handle == NULL) {
        return;
    }
    PHYSFS_uint32 length = PHYSFS_fileLength(handle);
    if (len != NULL) {
        *len = length;
    }
    if (addnull) {
        *mem = (unsigned char*)malloc(length + 1);
        (*mem)[length] = 0;
    } else {
        *mem = (unsigned char*)malloc(length);
    }
    int success = PHYSFS_readBytes(handle, *mem, length);
    if (success == -1) {
        free(*mem);
        *mem = NULL;
    }
    PHYSFS_close(handle);
}

Asset::Asset(const char* relative_asset_path)
    : asset_path(relative_asset_path)
{}

Asset::~Asset() {}

void Asset::load(bool addnull)
{
    unsigned char* fileIn = NULL;
    size_t length = 0;

    Resource::load2Mem(asset_path, &fileIn, &length, addnull);
    _load(fileIn, length);

    free(fileIn);

    if (!length) {
        std::string err_msg =
            std::string{ "Can't find asset-resource from path: " } + asset_path;
        throw std::invalid_argument(err_msg);
    }
}

PNGAsset::PNGAsset(const char* relative_asset_path)
    : Asset(relative_asset_path)
{
    if (!util::str::endsWith(relative_asset_path, ".png"))
        throw std::invalid_argument("PNGAsset need '.png' formatted file");

    load();
}
PNGAsset::~PNGAsset()
{
    if (asset)
        SDL_FreeSurface(asset);
}

void PNGAsset::_load(unsigned char* fileIn, size_t length)
{
    unsigned char* data;
    unsigned int w, h;

    lodepng_decode32(&data, &w, &h, fileIn, length);
    asset = SDL_CreateRGBSurfaceFrom(
        data, w, h, 32, w * 4, R_MASK, G_MASK, B_MASK, A_MASK);

    free(data);
}

JsonAsset::JsonAsset(const char* relative_asset_path)
    : Asset(relative_asset_path)
{
    load(true);
}

JsonAsset::~JsonAsset() {}
void JsonAsset::_load(unsigned char* fileIn, size_t length)
{
    asset = nlohmann::json::parse(fileIn);
}

FontAsset::FontAsset(const char* relative_asset_path)
    : Asset(relative_asset_path)
{
    load(true);
}

FontAsset::~FontAsset() {}
void FontAsset::_load(unsigned char* fileIn, size_t length)
{
    if (fileIn != NULL) {
        unsigned char* cur = fileIn;
        unsigned char* end = fileIn + length;
        int pos = 0;
        while (cur != end) {
            int codepoint = utf8::unchecked::next(cur);
            font_positions[codepoint] = pos;
            ++pos;
        }
    }
}
int FontAsset::getFontIdx(uint32_t ch)
{
    if (font_positions.size() > 0) {
        auto iter = font_positions.find(ch);
        if (iter == font_positions.end()) {
            iter = font_positions.find('?');
            if (iter == font_positions.end()) {
                throw std::out_of_range("font.txt missing fallback character!");
            }
        }
        return iter->second;
    } else {
        return ch;
    }
};

int FontAsset::getFontLen(uint32_t ch)
{
    return ch < 32 ? 6 : 8;
}

TileAsset::TileAsset(const char* relatvie_asset_path, SDL_Point size)
    : PNGAsset(relatvie_asset_path)
    , _size(size)
{
    load();
}

TileAsset::~TileAsset()
{
    for (auto tile : tiles)
        if (tile)
            SDL_FreeSurface(tile);
}

void TileAsset::_load(unsigned char* fileIn, size_t length)
{
    PNGAsset::_load(fileIn, length);

    for (int j = 0; j < asset->h; j += _size.x)
        for (int i = 0; i < asset->w; i += _size.y)
            tiles.push_back(GetSubSurface(SDL_Rect{ i, j, _size.x, _size.y }));
}

SDL_Surface* TileAsset::getTile(unsigned int i) const
{
    return tiles[i];
}