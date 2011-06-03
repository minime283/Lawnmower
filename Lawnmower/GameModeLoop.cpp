#ifndef GAMEMODELOOP_CPP
#define GAMEMODELOOP_CPP
#include "gamemodeloop.h"
GameModeLoop* GameModeLoop::next = nullptr;
int GameModeLoop::windowwidth;
int GameModeLoop::windowheight;
bool GameModeLoop::isRunning()
{
	return running;
}
#endif