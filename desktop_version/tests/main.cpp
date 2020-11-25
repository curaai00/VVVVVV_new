#include "gtest/gtest.h"
#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <physfs.h>

int main(int argc, char *argv[])
{
#ifdef __WIN32__
    char *assetPath = "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
#else
    char *assetPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
#endif

    PHYSFS_init(assetPath);
    if (!PHYSFS_mount(assetPath, NULL, 1))
    {
        std::invalid_argument("AssetPath is Invalid");
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}