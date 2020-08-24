#include "gtest/gtest.h"
#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "../src/editor.h"
#include "../src/Enums.h"
#include "../src/Entity.h"
#include "../src/FileSystemUtils.h"
#include "../src/Game.h"
#include "../src/Graphics.h"
#include "../src/Input.h"
#include "../src/KeyPoll.h"
#include "../src/Logic.h"
#include "../src/Map.h"
#include "../src/Music.h"
#include "../src/Network.h"
#include "../src/preloader.h"
#include "../src/Render.h"
#include "../src/Screen.h"
#include "../src/Script.h"
#include "../src/SoundSystem.h"
#include "../src/UtilityClass.h"

scriptclass script;

#if !defined(NO_CUSTOM_LEVELS)
std::vector<edentities> edentity;
editorclass ed;
#endif

UtilityClass help;
Graphics graphics;
musicclass music;
Game game;
KeyPoll key;
mapclass map;
entityclass obj;
Screen gameScreen;


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}