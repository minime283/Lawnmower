#include "winloop.h"
WinLoop::WinLoop(Mower* winner, int fieldsize)
{
	this->winner = winner;
	this->fieldsize = fieldsize;
}
WinLoop::~WinLoop()
{
}
void WinLoop::init()
{
	//Creates the loop object with the win textdisplay object
	text = new TextDisplay(0,0,50);
	text->setColor(255,0,0);
	sprintf(msg,"Player %i Wins!",winner->getMIndex()+1);
}
void WinLoop::checkEvents()
{
	//be sure to check events for the SDL_Quit event
	SDL_Event Event;
	while(SDL_PollEvent(&Event)) {
		switch(Event.type) {
			case SDL_QUIT:
				running=false;
				break;
		}}
}

void WinLoop::simulation()
{
}
void WinLoop::interpolateState()
{
}
void WinLoop::render()
{
	//simply draw text to the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0.0,0.0,windowwidth,windowheight);
	glColor3f(255,255,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(255,0,0);
	text->drawText(msg);
	SDL_GL_SwapBuffers();
}