#ifndef PROPERTIES_H
#define PROPERTIES_H
/**
Properties
Original hardcoded properties, will eventually be customizable from a menu
**/
//struct lmkeyboard {
	//SDLKey up;
/*	SDLKey down;
	SDLKey left;
	SDLKey right;
}
struct lmkeyboard {
	SDLAxis 
}
	SDLKey moveup = SDLK_UP;
	SDLKey movedown = SDLK_DOWN;
	SDLKey moveleft = SDLK_LEFT;
	SDLKey moveright = SDLK_RIGHT;
	

	*/
struct MowerSettings
{
	SDLKey moveup;
	SDLKey movedown;
	SDLKey moveleft;
	SDLKey moveright;
	GLfloat handlecol[4];
	GLfloat squarecol[4];
	GLfloat motorcol[4];
};


static MowerSettings msettings[4] =
{{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1}
},
{
	SDLK_w,
	SDLK_s,
	SDLK_a,
	SDLK_d,
	{0,1,1,1},
	{1,1,0,1},
	{1,0,1,1}
},
{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
},
{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
	}};

static SDLKey reset = SDLK_HOME;	
#endif