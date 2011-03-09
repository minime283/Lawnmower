#ifndef GAMEMODELOOP_H
#define GAMEMODELOOP_H
class GameModeLoop
{
protected:
	bool running;
public:
	bool isRunning()
	{
		return running;
	}
	virtual void init() = 0;
	virtual void checkEvents() = 0;
	virtual void simulation() = 0;
	virtual void interpolateState() = 0;
	virtual void render() = 0;
	static int windowwidth;
	static int windowheight;
};
#endif
