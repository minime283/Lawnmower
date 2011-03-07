#ifndef MOWER_H
#define MOWER_H
#include "grassfield.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_joystick.h"
class Mower
{
private:
	void checkCollision();
	void drawModel();
	void initModel();
	//Moves the lawnmower after inputs taken
	GLfloat conx;
	GLfloat cony; 
	//Variables for lawnmower position
	GLfloat lup;
	GLfloat lright;
	GLfloat lrotation;
	MowerSettings settings;
	void init(int index)
	{
		modelid = glGenLists(1);
		settings = msettings[index];
		Mower::count++;
		initModel();
		score = 0;
		conx = 0.0f;
		cony = 0.0f;
		lup = 0.0f;
		lright =0.0f;
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
protected:
	static Mower* mowers[4];
	
	static int count;
	void handleKeyboardUp(SDL_KeyboardEvent Event);
	void handleKeyboardDown(SDL_KeyboardEvent Event);
	void handleJoystickAxis(SDL_JoyAxisEvent Event);
public:
	Mower()
	{
	}
static void Mower::keyboardUp(SDL_KeyboardEvent Event)
{
	for(int i=0; i <= Mower::count -1; i ++) {
		Mower::mowers[i]->handleKeyboardUp(Event);
	}
}

static void Mower::keyboardDown(SDL_KeyboardEvent Event)
{
	for(int i=0; i <= Mower::count -1; i ++) {
		Mower::mowers[i]->handleKeyboardDown(Event);
	}
}
static void Mower::joystickAxis(SDL_JoyAxisEvent Event)
{
	for(int i=0; i <= Mower::count -1; i ++) {
		Mower::mowers[i]->handleJoystickAxis(Event);
	}
}
static void Mower::processMovementAll()
{
	for(int i=0; i <= Mower::count -1; i ++) {
		Mower::mowers[i]->processMovement();
	}
}
static void Mower::makeMower(int index)
{
	Mower::mowers[index] = new Mower();
	Mower::mowers[index]->init(index);
	
}
static void Mower::drawAll()
{
	for(int i=0; i <= Mower::count -1; i++) {
		Mower::mowers[i]->draw();
	}
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