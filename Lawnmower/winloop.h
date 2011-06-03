#ifndef WINLOOP_H
#define WINLOOP_H
#include "gamemodeloop.h"
#include "mower.h"
#include "textdisplay.h"
/**
This GameMode replaces the gameplay GameMode when the level completes, and displays the winner in plain text.
**/
class WinLoop : public GameModeLoop {
public:
	/**
	Common to all GameMode Loops
	**/
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
	/**
	Destructs the WinLoop
	**/
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
