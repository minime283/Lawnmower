#ifndef MOWER_H
#define MOWER_H
#include "grassfield.h"
#include "SDL.h"
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
	/**
	**/
	//int clast_update;
	GLfloat clast_up;
	GLfloat clast_right;
	/**
	Draws the model
	**/
	void drawModel();
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
	GLfloat vely; 
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
	void init(int index)
	{
		last_update = 0;
		//clast_update = 0;
		clast_up = 5.0f;
		clast_right = 5.0f;
		modelid = glGenLists(1);
		settings = msettings[index];
		Mower::count++;
		initModel();
		score = 0;
		velx = 0.0f;
		vely = 0.0f;
		accx = 0.0f;
		accy = 0.0f;
		lup = 5.0f;
		lright =5.0f;
		lrotation =0.0f;
	}
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
	int jid;
	/**displaylist id **/
	int modelid;
		static MowerSettings msettings[4];
protected:
	static Mower* mowers[4];
	
	static int count;

public:
	/**
	Checks the collision of the mower and the grass/other mowers
	**/
	void checkCollision();
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
	Mower(int index)
	{
		init(index);
	}
	~Mower()
	{
		glDeleteLists(1,modelid);
	}
	/**
	Returns up coordinate
	**/
	GLfloat getUp()
	{
		return this->lup;
	}
	/**
	Returns right coordinate
	**/
	GLfloat getRight()
	{
		return this->lright;
	}
	/**
	Sets the field 
	**/
	void setField(GrassField *field)
	{
		this->field = field;
	}
	/**
	Processes the movement position for this cycle
	**/
	void processMovement();
	/**
	Draws this lawnmower
	**/
	void draw();
	
};
#endif