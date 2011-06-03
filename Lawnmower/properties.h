#ifndef PROPERTIES_H
#define PROPERTIES_H

/**
Structure for a set of mower settings
**/
struct MowerSettings
{
	//Key controls for moving
	SDLKey moveup;
	SDLKey movedown;
	SDLKey moveleft;
	SDLKey moveright;
	//Colors
	GLfloat handlecol[4];
	GLfloat squarecol[4];
	GLfloat motorcol[4];
	//lawnmower attributes
	float acceleration;
	float maxvelocity;
	//starting position
	float startup;
	float startright;
};



static SDLKey reset = SDLK_HOME;	
#endif