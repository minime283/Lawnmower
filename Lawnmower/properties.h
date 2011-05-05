#ifndef PROPERTIES_H
#define PROPERTIES_H

/**
Structure for a set of mower settings
**/
struct MowerSettings
{
	SDLKey moveup;
	SDLKey movedown;
	SDLKey moveleft;
	SDLKey moveright;
	GLfloat handlecol[4];
	GLfloat squarecol[4];
	GLfloat motorcol[4];
	float acceleration;
	float maxvelocity;
	float startup;
	float startright;
};



static SDLKey reset = SDLK_HOME;	
#endif