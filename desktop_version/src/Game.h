#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include <vector>

#include "Menu.h"

bool GetButtonFromString(const char* pText, SDL_GameControllerButton* button);

struct CustomLevelStat
{
    std::string name;
    int score; // 0 - not played, 1 - finished, 2 - all trinkets, 3 - finished,
               // all trinkets
};

class Game
{
public:
    void init(void);

    int crewrescued();

    std::string unrescued();

    void resetgameclock();

    void customsavequick(std::string savfile);
    void savequick();

    void gameclock();

    std::string giventimestring(int hrs, int min, int sec);

    std::string timestring();

    std::string partimestring();

    std::string resulttimestring();

    std::string timetstring(int t);

    void returnmenu();
    void returntomenu(enum Menu::name t);
    void createmenu(enum Menu::name t, bool samemenu = false);

    void lifesequence();

    void gethardestroom();

    void updatestate();

    void unlocknum(int t);

    void loadstats(int* width, int* height, bool* vsync);

    void savestats();

    void deletestats();

    void deletequick();

    void savetele();

    void loadtele();

    void deletetele();

    void customstart();

    void start();

    void startspecial(int t);

    void starttrial(int t);

    void swnpenalty();

    void deathsequence();

    void customloadquick(std::string savfile);
    void loadquick();

    void loadsummary();

    void initteleportermode();

    std::string saveFilePath;

    int door_left;
    int door_right;
    int door_up;
    int door_down;
    int roomx, roomy, roomchangedir;
    int prevroomx, prevroomy;

    int savex, savey, saverx, savery;
    int savegc, savedir;

    // Added for port
    int edsavex, edsavey, edsaverx, edsavery;
    int edsavegc, edsavedir;

    // State logic stuff
    int state, statedelay;

    bool glitchrunkludge;

    int usingmmmmmm;

    int gamestate;
    bool hascontrol, jumpheld;
    int jumppressed;
    int gravitycontrol;

    bool muted;
    int mutebutton;
    bool musicmuted;
    int musicmutebutton;

    int tapleft, tapright;

    // Menu interaction stuff
    bool mapheld;
    int menupage;
    int lastsaved;
    int deathcounts;

    int frames, seconds, minutes, hours;
    bool gamesaved;
    std::string savetime;
    std::string savearea;
    int savetrinkets;
    bool startscript;
    std::string newscript;

    int mainmenu;
    bool menustart;

    // Teleporting
    bool teleport_to_new_area;
    int teleport_to_x, teleport_to_y;
    std::string teleportscript;
    bool useteleporter;
    int teleport_to_teleporter;

    // Main Menu Variables
    SimpleMenu menu_;

    // non-standard
    std::vector<MenuStackFrame> menustack;

    int current_credits_list_index;
    int creditposx, creditposy, creditposdelay;
    int oldcreditposx;

    // Sine Wave Ninja Minigame
    bool swnmode;
    int swngame, swnstate, swnstate2, swnstate3, swnstate4, swndelay, swndeaths;
    int swntimer, swncolstate, swncoldelay;
    int swnrecord, swnbestrank, swnrank, swnmessage;

    // SuperCrewMate Stuff
    bool supercrewmate, scmhurt, scmmoveme;
    int scmprogress;

    // Accessibility Options
    bool colourblindmode;
    bool noflashingmode;
    int slowdown;
    Uint32 gameframerate;

    bool nodeathmode;
    int gameoverdelay;
    bool nocutscenes;

    // Time Trials
    bool intimetrial, timetrialparlost;
    int timetrialcountdown, timetrialshinytarget, timetriallevel;
    int timetrialpar, timetrialresulttime, timetrialresultframes, timetrialrank;

    int creditposition;
    int oldcreditposition;
    bool insecretlab;

    bool inintermission;

    static const int numcrew = 6;
    bool crewstats[numcrew];

    bool alarmon;
    int alarmdelay;
    bool blackout;

    bool tele_crewstats[numcrew];

    bool quick_crewstats[numcrew];

    static const int numunlock = 25;
    bool unlock[numunlock];
    bool unlocknotify[numunlock];
    bool anything_unlocked();
    int stat_trinkets;
    bool fullscreen;
    int bestgamedeaths;

    static const int numtrials = 6;
    int besttimes[numtrials];
    int bestframes[numtrials];
    int besttrinkets[numtrials];
    int bestlives[numtrials];
    int bestrank[numtrials];

    std::string tele_gametime;
    int tele_trinkets;
    std::string tele_currentarea;
    std::string quick_gametime;
    int quick_trinkets;
    std::string quick_currentarea;

    int mx, my;
    int screenshake, flashlight;
    bool advancetext, pausescript;

    int deathseq, lifeseq;

    int trinkets();
    int crewmates();
    int savepoint, teleportxpos;
    bool teleport;
    int edteleportent;
    bool completestop;

    float inertia;

    int companion;
    bool roomchange;
    SDL_Rect teleblock;
    bool activetele;
    int readytotele;
    int oldreadytotele;
    int activity_r, activity_g, activity_b;
    std::string activity_lastprompt;

    std::string telesummary, quicksummary, customquicksummary;
    bool save_exists();

    bool backgroundtext;

    int activeactivity, act_fade;
    int prev_act_fade;

    bool press_left, press_right, press_action, press_map;

    // Some stats:
    int totalflips;
    std::string hardestroom;
    int hardestroomdeaths, currentroomdeaths;

    bool savemystats;

    bool fullScreenEffect_badSignal;
    bool useLinearFilter;
    int stretchMode;
    int controllerSensitivity;

    bool quickrestartkludge;

    // Custom stuff
    std::string customscript[50];
    int customcol;
    int levelpage;
    int playcustomlevel;
    std::string customleveltitle;
    std::string customlevelfilename;

    void clearcustomlevelstats();
    void loadcustomlevelstats();
    void savecustomlevelstats();
    void updatecustomlevelstats(std::string clevel, int cscore);

    std::vector<CustomLevelStat> customlevelstats;
    bool customlevelstatsloaded;

    std::vector<SDL_GameControllerButton> controllerButton_map;
    std::vector<SDL_GameControllerButton> controllerButton_flip;
    std::vector<SDL_GameControllerButton> controllerButton_esc;
    std::vector<SDL_GameControllerButton> controllerButton_restart;

    bool skipfakeload;
    bool ghostsenabled;

    bool cliplaytest;
    int playx;
    int playy;
    int playrx;
    int playry;
    int playgc;
    int playmusic;
    std::string playassets;

    void quittomenu();
    void returntolab();
    bool fadetomenu;
    int fadetomenudelay;
    bool fadetolab;
    int fadetolabdelay;

#if !defined(NO_CUSTOM_LEVELS)
    void returntoeditor();
    bool shouldreturntoeditor;
#endif

    int gametimer;

    bool inline inspecial()
    {
        return inintermission || insecretlab || intimetrial || nodeathmode;
    }

    bool over30mode;
    bool glitchrunnermode; // Have fun speedrunners! <3 Misa

    bool ingame_titlemode;

    bool shouldreturntopausemenu;
    void returntopausemenu();
    void unlockAchievement(const char* name);

    bool disablepause;
};

extern Game game;

#endif /* GAME_H */
