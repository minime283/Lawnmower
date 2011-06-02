#ifndef MOWER_H
#define MOWER_H
#include "grassfield.h"
#include "SDL.h"
#include <math.h>
#include "SDL_opengl.h"
#include "SDL_joystick.h"
#include "properties.h"

class Mower
{
private:
	/**
	When the last update happened in ms
	**/
	int last_update;
	int clast_update;
	bool prevcol;
	static const float radius;
	static const float mass;
	static const float coeff;
	bool Mower::doMowersCollide(float m1up,float m1right,float m2up,float m2right);
	/**
	Used to detect collision resolution, position of lawnmower at previous collision detection
	**/
	GLfloat clast_up;
	GLfloat clast_right;
	
	/**
	Initializes the model
	**/
	void initModel();
	/**
	Draws a 1x1x1 cube, to be translated to make part of the lawnmower
	**/
	void drawCube(int size);

	//Moves the lawnmower after inputs taken
	/**
	velocity of the lawnmower
	**/
	GLfloat velx;
	GLfloat velz; 
	/**
	acceleration of the lawnmower
	**/
	GLfloat accx;
	GLfloat accy;
	/**
	Lawnmower position
	**/
	GLfloat lup;
	GLfloat lright;
	GLfloat lrotation;
	MowerSettings settings;
	/**
	Pointer to the parent field
	**/
	GrassField* field;
	/**
	Initializes the lawnmower
	**/
	void Mower::init(int index);
	/**
	Score of the player
	**/
	int score;
	/**
	Index of the current lawnmower
	**/
	int index;
	/**
	Controls for up, down, left, right
	**/
	SDLKey kup;
	SDLKey kdown;
	SDLKey kleft;
	SDLKey kright;
	/**
	Controls for joystick
	**/
	int jaxisy;
	int jaxisx;
	//joystick id
	int jid;
	//id for storing the model in a display list
	int modelid;
	static MowerSettings msettings[4];
protected:
	static Mower* mowers[4];
	char sscore[10];
	static int count;

public:
	/**
	Gets the Score in int form
	**/
	int getNumScore();
	/**
	Gets the Score in a formatted string
	**/
	const char* getScore();
	/**
	Checks the collision of the mower and the edges of the screen
	**/
	void checkCollision();
	/**
	Checks and resolves collision between this mower and another mower
	**/
	void checkMowerCollision(Mower *othermower);
	/**
	Checks collision between mower and grass
	**/
	void checkGrassCollision();
	/**
	Handles a key being unpressed
	**/
	void handleKeyboardUp(SDL_KeyboardEvent Event);
	/**
	Handles a key being pressed
	**/
	void handleKeyboardDown(SDL_KeyboardEvent Event);
	/**
	Handles a joysitck being moved
	**/
	void handleJoystickAxis(SDL_JoyAxisEvent Event);
	/**
	Creates a new mower instance based on mower type
	**/
	Mower(int index);
	/**
	Cleans up the mower
	**/
	~Mower();
	/**
	Returns up coordinate
	**/
	GLfloat getUp();
	/**
	Sets the up coordinate
	**/
	void setUp(GLfloat up);
	/**
	Returns right coordinate
	**/
	GLfloat getRight();
	/**
	Sets the right coordinate
	**/
	void setRight(GLfloat right);
	/**
	Gets the up at the previous collision check
	**/
	GLfloat getLastUp();
	/**
	Gets the previous position of right
	**/
	GLfloat getLastRight();
	/**
	Gets the current velocity in the X direction
	**/
	GLfloat Mower::getVelocityX();
	/**
	Sets the current velocity in the X direction
	**/
	void setVelocityX(GLfloat velx);
	/**
	Sets the current velocity in the Z direction
	**/
	void setVelocityZ(float velz);
	/**
	Gets the current velocity in the Z direction
	**/
	GLfloat getVelocityZ();

	/** 
	Gets the mower index
	**/
	int getMIndex();
	/**
	Updates the last collision check
	**/
	void updateLastCollisionCheck();
	/**
	Sets the field 
	**/
	void setField(GrassField *field);
	/**
	Gets the settings struct
	**/
	MowerSettings getSettings();
	/**
	Processes the movement position for this cycle
	**/
	void processMovement();
	/**
	Draws this lawnmower
	**/
	void draw();
	/**
	Draws the model
	**/
	void drawModel();
};
#endif