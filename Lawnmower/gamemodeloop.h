#ifndef GAMEMODELOOP_H
#define GAMEMODELOOP_H
/**
This class is a base class that all game modes inherit
Game modes can be the level, the menus, pause, etc.
**/
class GameModeLoop
{
protected:
	bool running;
public:
	/**
	Whether the game is over, or if it's quitting
	**/
	bool isRunning()
	{
		return running;
	}
	/**
	Initializes the loop
	**/
	virtual void init() = 0;
	/**
	Checks the events such as keypress, joystick press, etc.
	**/
	virtual void checkEvents() = 0;
	/**
	Runs the simulation loop such as collision detection, etc.
	**/
	virtual void simulation() = 0;
	/**
	Interpolates state of the objects without the simulation step
	**/
	virtual void interpolateState() = 0;
	/**
	Renders the scene
	**/
	virtual void render() = 0;
	/**
	Width of the window in pixels
	**/
	static int windowwidth;
	/**
	Height of the window in pixels
	**/
	static int windowheight;
};
#endif
