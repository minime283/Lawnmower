#ifndef WINLOOP_H
#define WINLOOP_H
#include "gamemodeloop.h"
#include "mower.h"
#include "textdisplay.h"
/**
Loop involving when the win state happens 
**/
class WinLoop : public GameModeLoop {
public:
	void init();
	void checkEvents();
	void simulation();
	void interpolateState();
	void render();
	/**
	@param Mower winner the Mower that won the round
	@param int fieldsize the size of the field
	**/
	WinLoop(Mower* winner, int fieldsize);
	
	~WinLoop();
private:
	/**
	The Winner of the round
	**/
	Mower* winner;
	/**
	The size of the field
	**/
	int fieldsize;
	/**
	The you've won text object
	**/
	TextDisplay* text;
	/**
	The text to display
	**/
	char msg[14];
};
#endif
