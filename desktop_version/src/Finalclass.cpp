#include "Finalclass.h"

#include "Entity.h"
#include "Game.h"
#include "MakeAndPlay.h"
#include "UtilityClass.h"

// clang-format off
const short* finalclass::loadlevel(int rx, int ry)
{
	int t;

	t = rx + (ry * 100);
	const short* result;
	warpx = false;
	warpy = false;

	roomname = "Untitled room ["+help.String(rx) + "," + help.String(ry)+"]";

	switch(t)
	{
#if !defined(MAKEANDPLAY)
	case rn(41,52):
	{

		static const short contents[] = {
		};


		if(!obj.flags[72])
		{
			if (game.intimetrial || game.nocutscenes)
			{
				obj.createblock(1, 152 - 4, 112, 20, 16, 85);
			}
			else
			{
				obj.createblock(5, 152 - 4, 112, 20, 16, 13);
			}
		}

		warpx = true;
		warpy = true;
		roomname = "DIY V Repair";
		result = contents;
		break;
	};

	case rn(48,52):
	{

		static const short contents[] = {
		};


		roomname = "The Villi People";
		result = contents;
		break;
	}

	case rn(50,53):
	{

		static const short contents[] = {
		};


		roomname = "change";
		result = contents;
		break;
	}

	case rn(50,54):
	{

		static const short contents[] = {
		};


		roomname = "change";
		result = contents;
		break;
	}


	case rn(52,53):
	{

		static const short contents[] = {
		};


		roomname = "The Last Straw";
		result = contents;
		break;
	}

	case rn(53,53):
	{

		static const short contents[] = {
		};


		roomname = "W";
		result = contents;
		break;
	}

	case rn(54,53):
	{

		static const short contents[] = {
		};


		roomname="V";
		result = contents;
		break;
	}


	case rn(54,52):
	{

		static const short contents[] = {
		};
		roomname = "VV";
		result = contents;
		break;
	}


	case rn(54,51):
	{

		static const short contents[] = {
		};
		roomname = "VVV";
		result = contents;
		break;
	}


	case rn(54,50):
	{

		static const short contents[] = {
		};
		roomname = "VVVV";
		result = contents;
		break;
	}

	case rn(54,49):
	{

		static const short contents[] = {
		};

		roomname = "VVVVV";
		result = contents;
		break;
	}

	case rn(54,48):
	{

		static const short contents[] = {
		};

		obj.createblock(0, 0, 0, 5, 240);
		obj.createblock(0, 315, 0, 5, 240);


		if(game.intimetrial)
		{
			obj.createblock(1, 0, 0, 320, 120, 82);
		}
		else
		{
			obj.createblock(1, 0, 0, 320, 120, 3500); //Game complete
		}
		roomname = "VVVVVV";
		result = contents;
		break;
	}


	case rn(46,54):
	{

		static const short contents[] = {
		};

		warpy = true;
		roomname = "Temporary Fault...";
		result = contents;
		break;
	}

	case rn(47,54):
	{

		static const short contents[] = {
		};
		warpy = true;
		roomname = "Do Not Adjust the V-hold";
		result = contents;
		break;
	}

	case rn(48,54):
	{

		static const short contents[] = {
		};


		/*if(!game.nocutscenes && !obj.flags[71]){
		obj.createblock(1, 72, 0, 320, 240, 49);
		}*/

		warpy = true;
		roomname = "Regular Service Will Return Shortly";
		result = contents;
		break;
	}

	case rn(49,54):
	{

		static const short contents[] = {
		};

		warpy = true;
		roomname = "Origami Room";
		result = contents;
		break;
	}


		//Tower Hallways from here
	case rn(108,109):
	{

		static const short contents[] = {
		};

		roomname = "Teleporter Divot";
		result = contents;
		break;
	}

	case rn(110,104):
	{

		static const short contents[] = {
		};

		roomname = "Seeing Red";

		if(!game.intimetrial)
		{
			if(game.companion==0 && !obj.flags[8] && !game.crewstats[3])   //also need to check if he's rescued in a previous game
			{
				obj.createentity(264, 185, 18, 15, 1, 17, 0);
				obj.createblock(1, 26*8, 0, 32, 240, 36);
			}
		}
		result = contents;
		break;
	}

	case rn(111,104):
	{

		static const short contents[] = {
		};

		roomname = "Building Apport";

		if(game.intimetrial)
		{
			obj.createblock(1, 40, 0, 32, 240, 82);
		}
		result = contents;
		break;
	}

		//Intermission level 2
	case rn(53,48):
	{

		static const short contents[] = {
		};

		roomname = "Whee Sports";
		warpx = true;
		result = contents;
		break;
	}

	case rn(53,49):
	{

		static const short contents[] = {
		};

		roomname = "Whizz Down The Shaft";
		warpx = true;
		result = contents;
		break;
	}

	case rn(53, 50):
	{
		static const short contents[] = {
		};


		//obj.createentity(-8, 84-32, 11, 328);  // (horizontal gravity line)
		obj.createentity(-8, 148 + 32, 11, 328);  // (horizontal gravity line)

		obj.createblock(1, -10, 84 - 16, 340, 32, 10); //create the second line!

		roomname = "The Gravitron";
		warpx = true; //warpy = true;
		result = contents;
		break;
	}

	case rn(53,51):
	{

		static const short contents[] = {
		};


		if(game.companion==0)   //also need to check if he's rescued in a previous game
		{
			if (game.lastsaved == 2)
			{
				obj.createentity(112, 169, 18, 14, 0, 17, 1);
				obj.createblock(1, 22 * 8, 16*8, 32, 240, 37);
			}
			else if (game.lastsaved ==3)
			{
				obj.createentity(112, 169, 18, 15, 0, 17, 1);
				obj.createblock(1, 22 * 8, 16*8, 32, 240, 38);
			}
			else if (game.lastsaved == 4)
			{
				obj.createentity(112, 169, 18, 13, 0, 17, 1);
				obj.createblock(1, 22 * 8, 16*8, 32, 240, 39);
			}
			else
			{
				obj.createentity(112, 169, 18, 16, 1, 17, 1);
				obj.createblock(1, 22 * 8, 16*8, 32, 240, 40);
			}
		}

		roomname = "Tunnel of Terror";
		warpx = true;

		game.swnmode = false;
		result = contents;
		break;
	}


	case rn(53,52):
	{

		static const short contents[] = {
		};


		roomname = "House of Mirrors";
		warpx = true;
		result = contents;
		break;
	}

		//Intermission 1

	case rn(41,56):
	{

		static const short contents[] = {
		};

		//obj.createentity(164, 96, 10, 1, 56410);  // (savepoint)

		warpy = true;
		roomname = "Now Take My Lead";
		result = contents;
		break;
	}


	case rn(42,56):
	{

		static const short contents[] = {
		};

		if(!game.nodeathmode)
		{
			obj.createblock(1, 0, 0, 32, 240, 41); //scene 2
			obj.createblock(1, 280, 0, 32, 240, 12); //scene 2
		}

		roomname = "What Are You Waiting For?";
		warpy = true;
		result = contents;
		break;
	}

	case rn(43,56):
	{

		static const short contents[] = {
		};

		if(!game.nodeathmode)
		{
			obj.createblock(1, 20, 0, 32, 240, 13); //scene 2
		}

		warpy = true;
		roomname = "Don't Get Ahead of Yourself!";
		result = contents;
		break;
	}

	case rn(44,56):
	{

		static const short contents[] = {
		};


		if(!game.nodeathmode)
		{
			obj.createblock(1, 200, 0, 32, 240, 42); //scene 3
		}


		roomname = "Very Good";
		warpy = true;
		result = contents;
		break;
	}

	case rn(45,56):
	{

		static const short contents[] = {
		};


		roomname = "Must I Do Everything For You?";
		warpy = true;

		result = contents;
		break;
	}

	case rn(46,56):
	{

		static const short contents[] = {
		};


		if(!game.nodeathmode)
		{
			obj.createblock(1, 200, 0, 32, 240, 43); //scene 3
		}

		roomname = "Now Stay Close To Me...";
		warpy = true;
		result = contents;
		break;
	}

	case rn(47,56):
	{

		static const short contents[] = {
		};


		roomname = "...But Not Too Close";
		warpy = true;
		result = contents;
		break;
	}

	case rn(48,56):
	{

		static const short contents[] = {
		};

		warpy = true;
		roomname = "Don't Be Afraid";
		result = contents;
		break;
	}

	case rn(49,56):
	{

		static const short contents[] = {
		};

		if(!game.nodeathmode)
		{
			obj.createblock(1, 200, 0, 32, 240, 44); //scene 3
		}
		warpy = true;
		roomname = "Do as I Say...";
		result = contents;
		break;
	}

	case rn(50,56):
	{

		static const short contents[] = {
		};


		roomname = "...Not as I Do";
		warpy = true;
		result = contents;
		break;
	}

	case rn(51,56):
	{

		static const short contents[] = {
		};

		if(!game.nodeathmode)
		{
			obj.createblock(1, 80, 0, 32, 240, 45); //scene 3
		}
		warpy = true;
		roomname = "Mind Your Head";
		result = contents;
		break;
	}

	case rn(52,56):
	{

		static const short contents[] = {
		};


		roomname = "Do Try To Keep Up";
		warpy = true;
		result = contents;
		break;
	}

	case rn(53,56):
	{

		static const short contents[] = {
		};


		roomname = "You're Falling Behind";
		warpy = true;
		result = contents;
		break;
	}

	case rn(54,56):
	{

		static const short contents[] = {
		};


		if(!game.nodeathmode)
		{
			obj.createblock(1, 104, 0, 32, 240, 46); //scene 3
		}

		roomname = "Class Dismissed!";
		warpy = true;
		result = contents;
		break;
	}


#endif

	default:
	{
		static const short contents[1200] = {0};
		roomname = "Outer Space";

		//game.test = true;
		//game.teststring = "ERROR: Map not found in Final Area";
		result = contents;
		break;
	}
	}

	return result;
}

// clang-format on