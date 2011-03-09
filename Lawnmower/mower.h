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
	int last_update;
	void checkCollision();
	void drawModel();
	void initModel();
	void drawCube(int size);

	//Moves the lawnmower after inputs taken
	GLfloat velx;
	GLfloat vely; 
	//GLfloat accx;
	//GLfloat accy;
	//Variables for lawnmower position
	GLfloat lup;
	GLfloat lright;
	GLfloat lrotation;
	MowerSettings settings;
	GrassField* field;
	void init(int index)
	{
		last_update = 0;
		modelid = glGenLists(1);
		settings = msettings[index];
		Mower::count++;
		initModel();
		score = 0;
		velx = 0.0f;
		vely = 0.0f;
		lup = 5.0f;
		lright =5.0f;
		lrotation =0.0f;
	}
	int score;
	int index;
	SDLKey kup;
	SDLKey kdown;
	SDLKey kleft;
	SDLKey kright;
	int jaxisy;
	int jaxisx;
	int jid;
	int modelid;
		static MowerSettings msettings[4];
protected:
	static Mower* mowers[4];
	
	static int count;

public:
	void handleKeyboardUp(SDL_KeyboardEvent Event);
	void handleKeyboardDown(SDL_KeyboardEvent Event);
	void handleJoystickAxis(SDL_JoyAxisEvent Event);
	Mower()
	{
	}
	Mower(int index)
	{
		init(index);
	}

	GLfloat getUp()
	{
		return this->lup;
	}
	GLfloat getRight()
	{
		return this->lright;
	}

	void setField(GrassField *field)
	{
		this->field = field;
	}
	void processMovement();
	
	Mower(SDLKey up, SDLKey down, SDLKey left, SDLKey right)
	{
		init(1);
		kup = up;
		kdown = down;
		kleft = left;
		kright = right;
	}
	Mower(int axisx, int axisy, int joystick_id)
	{
		init(1);
		jaxisy = axisy;
		jaxisx = axisx;
		jid = joystick_id;		
	}
	void draw();
	
};
#endif