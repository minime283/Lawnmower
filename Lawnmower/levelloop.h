#ifndef LEVELLOOP_H
#define LEVELLOOP_H
#include "lawnmower.h"
#include "gamemodeloop.h"
#include "mower.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "grassfield.h"

class LevelLoop : public GameModeLoop {
public:
	void init();
	void checkEvents();
	void simulation();
	void interpolateState();
	void render();
	void addMower(int index);
	LevelLoop()
	{
		mowers[0] = nullptr;
		mowers[1] = nullptr;
		mowers[2] = nullptr;
		mowers[3] = nullptr;
	}
private:
	
	
	GrassField* field;
	void disp();
	Mower* mowers[4];
	int count;
	void handleResize(int width, int height);
};
#endif