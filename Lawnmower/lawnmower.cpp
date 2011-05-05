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
		if (curclock - prevclock > 17) {
			myloop->checkEvents();
			myloop->simulation();
		}	
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
	LevelLoop* myloop = new LevelLoop();
	myloop->addMower(0);
	myloop->addMower(1);
	runGameLoop(myloop);
	while (GameModeLoop::next != nullptr) {
		GameModeLoop* mynext = GameModeLoop::next;
		GameModeLoop::next = nullptr;
		runGameLoop(mynext);
	}
	SDL_Quit();
	return 0;
}
#endif