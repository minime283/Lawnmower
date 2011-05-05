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
	**/
	//int clast_update;
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
	void init(int index)
	{
		last_update = 0;
		clast_update =0;
		modelid = glGenLists(1);
		this->index = index;
		settings = msettings[index];
		Mower::count++;
		initModel();
		score = 0;
		velx = 0.0f;
		velz = 0.0f;
		accx = 0.0f;
		accy = 0.0f;
		clast_up = settings.startup;
		clast_right = settings.startright;
		lup = settings.startup;
		lright =settings.startright;
		lrotation =0.0f;
		prevcol = false;
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
	char sscore[10];
	static int count;

public:
	const char* getScore()
	{
		sprintf(sscore,"%i (%i%c)",score,(int)((float)score/(float)this->field->getTotalSquares()*100),'%');
		//score[strlen(score)] = '\0';
		return sscore;
	}
	int getNumScore()
	{
		return score;
	}
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
	Mower(int index)
	{
		init(index);
	}
	/**
	Cleans up the mower
	**/
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
	Sets the up coordinate
	**/
	void setUp(GLfloat up)
	{
		this->lup = up;
	}
	/**
	Returns right coordinate
	**/
	GLfloat getRight()
	{
		return this->lright;
	}
	/**
	Sets the right coordinate
	**/
	void setRight(GLfloat right) 
	{
		this->lright = right;
	}
	/**
	Gets the up at the previous collision check
	**/
	GLfloat getLastUp()
	{
		return this->clast_up;
	}
	/**
	Gets the current velocity in the X direction
	**/
	GLfloat getVelocityX()
	{
		return this->velx;
	}
	/**
	Sets the current velocity in the X direction
	**/
	void setVelocityX(GLfloat velx)
	{
		this->velx = velx;
	}
	/**
	Sets the current velocity in the Z direction
	**/
	void setVelocityZ(float velz)
	{
		this->velz = velz;
	}
	/**
	Gets the current velocity in the Z direction
	**/
	GLfloat getVelocityZ()
	{
		return this->velz;
	}
	/**
	Gets the previous position of right
	**/
	GLfloat getLastRight()
	{
		return this->clast_right;
	}
	/** 
	Gets the mower index
	**/
	int getMIndex()
	{
		return this->index;
	}
	/**
	Updates the last collision check
	**/
	void updateLastCollisionCheck();
	/**
	Sets the field 
	**/
	void setField(GrassField *field)
	{
		this->field = field;
	}
	MowerSettings getSettings()
	{
		return settings;
	}
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