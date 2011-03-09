class GameModeLoop
{
	virtual void checkEvents();
	virtual void simulation();
	virtual void interpolateState();
	virtual void render();
};