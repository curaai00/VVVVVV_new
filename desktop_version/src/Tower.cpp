#include "Tower.h"

#include "FileSystemUtils.h"
#include "MakeAndPlay.h"
#include "UtilityClass.h"

// clang-format off
towerclass::towerclass()
{
	minitowermode = false;
	//We init the lookup table:
	for (size_t i = 0; i < SDL_arraysize(vmult); i++)
	{
		vmult[i] = i * 40;
	}
	//We create a blank map
	SDL_memset(contents, 0, sizeof(contents));
	SDL_memset(back, 0, sizeof(back));
	SDL_memset(minitower, 0, sizeof(minitower));

    auto parse_json = [](const char* path) -> nlohmann::json {
        unsigned char* uMem = NULL;
        FILESYSTEM_loadFileToMemory(path, &uMem, NULL, true);
        return nlohmann::json::parse(uMem);
    };

#ifdef __WIN32__
    char* assetsPath =
        "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
    char* argvZero =
        "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
#else
    char* assetsPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
    char* argvZero =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/VVVVVV_run";
#endif
    FILESYSTEM_init(argvZero, argvZero, assetsPath);
    tower_table = parse_json("tower.json");

	loadbackground();
	loadmap();
}

int towerclass::backat(int xp, int yp, int yoff)
{
	yp = yp * 8;
	yp += yoff;
	yoff = yp % 8;
	yp = (yp - yoff) / 8;

	if (xp >= 0 && xp < 40)
	{
		while (yp < 0) yp += 120;
		while (yp >= 120) yp -= 120;
		return back[xp + vmult[yp]];
	}
	return 0;
}

int towerclass::at(int xp, int yp, int yoff)
{
	if (minitowermode)
	{
		return miniat(xp, yp, yoff);
	}
	else
	{
		yp = yp * 8;
		yp += yoff;
		yoff = yp % 8;
		yp = (yp - yoff) / 8;

		while (yp < 0) yp += 700;
		while (yp >= 700) yp -= 700;
		if (xp >= 0 && xp < 40)
		{
			return contents[xp + vmult[yp]];
		}
		else if (xp == -1)
		{
			return contents[vmult[yp]];
		}
		else if (xp == 40)
		{
			return contents[39 + vmult[yp]];
		}
		return 0;
	}
}

int towerclass::miniat(int xp, int yp, int yoff)
{
	yp = yp * 8;
	yp += yoff;
	yoff = yp % 8;
	yp = (yp - yoff) / 8;

	while (yp < 0) yp += 100;
	while (yp >= 100) yp -= 100;
	if (xp >= 0 && xp < 40)
	{
		return minitower[xp + vmult[yp]];
	}
	else if (xp == -1)
	{
		return minitower[vmult[yp]];
	}
	else if (xp == 40)
	{
		return minitower[39 + vmult[yp]];
	}
	return 0;
}

void towerclass::loadminitower1()
{
	//Loads the first minitower into the array.
#if !defined(MAKEANDPLAY)
	short tmap[4000];
	auto tower = tower_table["minitower1"].get<std::vector<short>>();
	for(int i=0; i<tower.size(); i++)
		tmap[i] = tower[i];

	SDL_memcpy(minitower, tmap, sizeof(minitower));
#endif
}

void towerclass::loadminitower2()
{
#if !defined(MAKEANDPLAY)
	short tmap[4000];
	auto tower = tower_table["minitower2"].get<std::vector<short>>();
	for(int i=0; i<tower.size(); i++)
		tmap[i] = tower[i];
	SDL_memcpy(minitower, tmap, sizeof(minitower));
#endif
}


void towerclass::loadbackground()
{
	//Loads the background into the array.
	short tmap[4800];
	auto tower = tower_table["background"].get<std::vector<short>>();
	for(int i=0; i<tower.size(); i++)
		tmap[i] = tower[i];
	SDL_memcpy(back, tmap, sizeof(back));
}

void towerclass::loadmap()
{
	//Loads the map into the array.
#if !defined(MAKEANDPLAY)
	short tmap[28000];
	auto tower = tower_table["map"].get<std::vector<short>>();
	for(int i=0; i<tower.size(); i++)
		tmap[i] = tower[i];

	SDL_memcpy(contents, tmap, sizeof(contents));
#endif
}

// clang-format on