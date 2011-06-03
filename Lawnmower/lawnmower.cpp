#ifndef LAWNMOWER_CPP
#define LAWNMOWER_CPP
#include "lawnmower.h"
void runGameLoop(GameModeLoop* myloop)
{
	int prevclock = 0;
	int curclock = 0;
	myloop->init();
	while(myloop->isRunning()) {
		curclock = clock();
		//Only do the simulation step every 64ms (4 frames)
		if (curclock - prevclock > 64) {
			myloop->checkEvents();
			myloop->simulation();
		}
		//interpolate state and render as much as possible (best case once every frame for 60fps)
		myloop->interpolateState();
		myloop->render();
		prevclock = curclock;
	}
}

void initGL()
{
	SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); 

	SDL_Surface* screen = SDL_SetVideoMode(640,480,0,SDL_HWPALETTE | SDL_HWSURFACE |SDL_OPENGL);
	GameModeLoop::windowheight = 480;
	GameModeLoop::windowwidth = 640;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
int main(int argc, char** argv)
{
	initGL();
	//create sample level with two mowers
	LevelLoop* myloop = new LevelLoop();
	myloop->addMower(0);
	myloop->addMower(1);
	//run game loop
	runGameLoop(myloop);
	//if the game loop ends, we check to see if there is another gameloop waiting to replace it
	//(ex. when the win condition happens, the level loop queues up the "win loop" as the new game mode)
	//NOT a queue data structure. Doesn't make sense to want to queue two loops ahead, switching modes should be done sparingly.
	while (GameModeLoop::next != nullptr) {
		//set the game loop
		GameModeLoop* mynext = GameModeLoop::next;
		//clear the waiting game loop
		GameModeLoop::next = nullptr;
		//run the new loop in the runGameLoop function
		runGameLoop(mynext);
	}
	SDL_Quit();
	return 0;
}
#endif