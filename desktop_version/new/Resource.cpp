#include "Resource.h"

#include <exception>
#include <physfs.h>
#include <tinyxml2.h>

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

void PNGAsset::_load(unsigned char* fileIn, size_t length)
{
    unsigned char* data;
    unsigned int w, h;

    lodepng_decode24(&data, &w, &h, fileIn, length);
    asset = SDL_CreateRGBSurfaceFrom(
        data, w, h, 24, w * 3, 0x000000FF, 0x0000FF00, 0x00FF0000, 0x00000000);

    free(data);
}

JsonAsset::~JsonAsset() {}
void JsonAsset::_load(unsigned char* fileIn, size_t length)
{
    asset = nlohmann::json::parse(fileIn);
}