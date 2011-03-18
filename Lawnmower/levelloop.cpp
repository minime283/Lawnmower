#include "levelloop.h"
int GameModeLoop::windowwidth;
int GameModeLoop::windowheight;
void LevelLoop::init()
{
	field = new GrassField(40);

	for(int i = 0;i<=3;i++) {
		if(mowers[i] != nullptr) {
			mowers[i]->setField(field);
		}
	}
}
void LevelLoop::addMower(int index)
{
	mowers[index] = new Mower(index);
	int mycount = 0;
	for (int i = 0; i <=3; i++) {
		if(mowers[i] != nullptr) {
			mycount++;
		}
	}
	count = mycount;
}
void LevelLoop::checkEvents()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event)) {
		switch(Event.type) {
			case SDL_QUIT:
				running=false;
				break;
			case SDL_VIDEORESIZE:
				handleResize(Event.resize.w,Event.resize.h);
				break;								
			case SDL_KEYDOWN:
				for(int i=0;i<=3;i++) {
					if (mowers[i] != nullptr) {
						mowers[i]->handleKeyboardDown(Event.key);
					}
				}
				break;
			case SDL_KEYUP:
				for(int i=0;i<=3;i++) {
					if (mowers[i] != nullptr) {
						mowers[i]->handleKeyboardUp(Event.key);
					}
				}
				break;
			case SDL_JOYAXISMOTION:
				for(int i=0;i<=3;i++) {
					if (mowers[i] != nullptr) {
						mowers[i]->handleJoystickAxis(Event.jaxis);
					}
				}
				break;
		}
	}
}
void LevelLoop::handleResize(int width, int height)
{
	windowwidth = width;
	windowheight = height;
	glViewport(0.0,0.0,width,height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(double)width / (double)height ,1.0f,50.0f);
}
void LevelLoop::simulation()
{

}
void LevelLoop::interpolateState()
{
	for(int i=0;i<=3;i++) {
		if (mowers[i] != nullptr) {
			mowers[i]->processMovement();
		}
	}
}
void LevelLoop::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (count == 1) {
		glViewport(0.0,0.0,windowwidth,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight ,1.0f,50.0f);	
		disp();
	} else if(count == 2){
		glViewport(0.0,0.0,windowwidth/2,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight /2,1.0f,50.0f);	
		gluLookAt(-transX+mowers[0]->getRight(),-transY,-transZ+mowers[0]->getUp(),mowers[0]->getRight(),-mowers[0]->getUp(),0,0,2,0); //6,1,16,15,25,5,-1,-1,-1,
		disp();
		glViewport(windowwidth/2,0.0,windowwidth/2,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight /2,1.0f,50.0f);	
		gluLookAt(-transX+mowers[1]->getRight(),-transY,-transZ+mowers[1]->getUp(),mowers[1]->getRight(),-mowers[1]->getUp(),0,0,2,0); //6,1,16,15,25,5,-1,-1,-1,
		disp();
	} else {
		//3 or 4 mowers
	}
	SDL_GL_SwapBuffers();
}
void LevelLoop::disp()
{	
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-5.0f);
		field->render();
		for(int i=0;i<=3;i++) {
			if (mowers[i] != nullptr) {
				mowers[i]->draw();
			}
		}
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}