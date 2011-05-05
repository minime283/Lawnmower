#ifndef LEVELLOOP_H
#define LEVELLOOP_H
#include "textdisplay.h"
#include "gamemodeloop.h"
#include "winloop.h"
#include "mower.h"
#include "SDL.h"
#include <string>
#include "SDL_opengl.h"
#include "grassfield.h"
/**
This game mode loop specifically is targeted in the Levelloop
**/
class LevelLoop : public GameModeLoop {
public:
	void init();
	
	void checkEvents();
	void simulation();
	void interpolateState();
	void render();
	/**
	Adds a mower with that specific index
	@param int index
	**/
	void addMower(int index);
	LevelLoop()
	{
		mowers[0] = nullptr;
		mowers[1] = nullptr;
		mowers[2] = nullptr;
		mowers[3] = nullptr;
	}
	~LevelLoop()
	{
		for(int i=0;i<=3;i++) {
			if(mowers[i] != nullptr) 
				delete mowers[i];
		}
		delete field;
		delete mowers;
	}
private:
	/**
	The field for the level
	**/
	GrassField* field;
	/**
	Drawing for each viewport
	**/
	void disp();
	/**
	Each of the lawnmowers
	**/
	Mower* mowers[4];
	TextDisplay* scores[4];
	int count;
	void handleResize(int width, int height);
	static GLfloat transX; //Translate around the X axis
	static GLfloat transY; // Translate around the Y axis
	static GLfloat transZ; // Translate around the Z axis
};
#endif