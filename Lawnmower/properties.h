#ifndef PROPERTIES_H
#define PROPERTIES_H


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



static SDLKey reset = SDLK_HOME;	
#endif