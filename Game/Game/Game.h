#pragma once
#include "DrawEngine.h"
#include "GameEngine.h"
#include "Gui.h"

class Game
{

	Gui* gui;
	GameEngine* GEngine;
	DrawEngine* DEngine;
	boost::thread* GameLoop;


public:
	Game(int Height, int Width)
	{

		GEngine = new GameEngine();
		gui = new Gui(Height, Width, GEngine);
		DEngine = new DrawEngine(gui, GEngine);

		GameLoop = new boost::thread((*GEngine));//новий поток вперед))
	}

	void StartDraw()
	{
		DEngine->Loop();
	}
	void Loop()
	{
		gui->Proccesing();
		DEngine->Loop();
	}
	Gui* GetGui()
	{
		return gui;
	}
	~Game(void);
};

