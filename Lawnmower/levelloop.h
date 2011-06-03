#ifndef LEVELLOOP_H
#define LEVELLOOP_H
//Maximum number of Mowers
#define LEVELLOOP_MAXMOWERS 4
//Fieldsize for the field used
#define LEVELLOOP_FIELD_SIZE 40
#define LEVELLOOP_FIELD_NEAR 1
#define LEVELLOOP_FIELD_FAR 50
#define LEVELLOOP_FIELD_ANGLE 45
#define LEVELLOOP_CAMERA_UPX 0
#define LEVELLOOP_CAMERA_UPY 2
#define LEVELLOOP_CAMERA_UPZ 0
#include "textdisplay.h"
#include "gamemodeloop.h"
#include "winloop.h"
#include "mower.h"
#include "SDL.h"
#include <string>
#include "SDL_opengl.h"
#include "grassfield.h"
/**
This game mode is the mode that involves the actual gameplay.
**/
class LevelLoop : public GameModeLoop {
public:
	LevelLoop();
	~LevelLoop();

	/**
	The following are common to all Game Mode Loops
	**/
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
	
private:
	/**
	The field for the level
	**/
	GrassField* field;

	/**
	Drawing function, called for each viewport (eg twice for 2p splitscreen)
	**/
	void disp();

	/**
	Each of the lawnmowers
	**/
	Mower* mowers[4];

	/**
	Text objects for each of the scores
	**/
	TextDisplay* scores[4];
	
	/**
	Number of lawnmowers in this mode 
	**/
	int count;
	
	/**
	Handles the resize of the window
	**/
	void handleResize(int width, int height);

	/**
	Position of the camera
	**/
	static GLfloat transX;
	static GLfloat transY;
	static GLfloat transZ;
};
#endif