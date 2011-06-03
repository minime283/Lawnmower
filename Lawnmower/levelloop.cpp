#ifndef LEVELLOOP_CPP
#define LEVELLOOP_CPP
#include "levelloop.h"
GLfloat LevelLoop::transX = -6.0; //Translate around the X axis
GLfloat LevelLoop::transY = -11.0; // Translate around the Y axis
GLfloat LevelLoop::transZ = -25.0; // Translate around the Z axis
LevelLoop::LevelLoop()
{
	for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
		mowers[i] = nullptr;
	}
}
LevelLoop::~LevelLoop()
{
	for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
		if(mowers[i] != nullptr) 
			delete mowers[i];
	}
	delete field;
	delete mowers;
}

void LevelLoop::init()
{
	//Creates a new field (currently a static size 40 tall/40 wide)
	field = new GrassField(40);

	//
	for(int i = 0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
		scores[i] = nullptr;
		if(mowers[i] != nullptr) {
			mowers[i]->setField(field);
			scores[i] = new TextDisplay(0,0,25);
			scores[i]->setBackgroundColor(true,mowers[i]->getSettings().squarecol);
			if(count ==2) {
				scores[i]->setViewportParameters(windowwidth/2,windowheight/2);
			} else if(count>2) {
				scores[i]->setViewportParameters(windowwidth/4,windowheight/4);
			}
		}
	}
}
void LevelLoop::addMower(int index)
{
	mowers[index] = new Mower(index);
	int mycount = 0;
	for (int i = 0; i <=LEVELLOOP_MAXMOWERS - 1; i++) {
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
				for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
					if (mowers[i] != nullptr) {
						mowers[i]->handleKeyboardDown(Event.key);
					}
				}
				break;
			case SDL_KEYUP:
				for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
					if (mowers[i] != nullptr) {
						mowers[i]->handleKeyboardUp(Event.key);
					}
				}
				break;
			case SDL_JOYAXISMOTION:
				for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
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
	gluPerspective(LEVELLOOP_FIELD_ANGLE,(double)width / (double)height ,LEVELLOOP_FIELD_NEAR,LEVELLOOP_FIELD_FAR);
}
void LevelLoop::simulation()
{
	//Collision Check
	for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
		for(int j=i+1;j<=LEVELLOOP_MAXMOWERS - 1;j++) {
			if (mowers[i] != nullptr && mowers[j] != nullptr) {
				mowers[i]->checkMowerCollision(mowers[j]);
			}
		}
	}
	for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
		if (mowers[i] != nullptr) {
			mowers[i]->updateLastCollisionCheck();
		}
	}
	//Win Check
	//Check each mower
	for(int i=0; i<=3; i++) {
		//Don't check this mower if it doesn't exist
		if (mowers[i] == nullptr)
			continue;
		bool iswinner = true;
		//check this mower against every other mower;
		for(int j=0;j<=3;j++) {
			if (mowers[i] != nullptr) {				
				//This mower isn't valid
				if (i == j || mowers[j] == nullptr) 
					continue;
				//If another mower + remaining squares can concievably overtake this mower
				if ((mowers[j]->getNumScore() + field->getSquaresRemaining()) > mowers[i]->getNumScore()) {
					iswinner = false;
					break;
				}
			}
		}
		if (iswinner) {
			WinLoop *wloop = new WinLoop(mowers[i],this->field->getFieldSize());
			next = wloop;
			this->running = false;
		}
	}
		//If this mower is the winner, check the win condition
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
	//Draws each viewport
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (count == 1) {
		//For 1 player, draw using the whole window
		glViewport(0.0,0.0,windowwidth,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight ,LEVELLOOP_FIELD_NEAR,LEVELLOOP_FIELD_FAR);	
		disp();
	} else if(count == 2){
		//For 2 player, split the window in half horizontally
		glViewport(0.0,0.0,windowwidth/2,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight /2,LEVELLOOP_FIELD_NEAR,LEVELLOOP_FIELD_FAR);	
		gluLookAt(-transX+mowers[0]->getRight(),-transY,-transZ+mowers[0]->getUp(),mowers[0]->getRight(),-mowers[0]->getUp(),0,LEVELLOOP_CAMERA_UPX,LEVELLOOP_CAMERA_UPY,LEVELLOOP_CAMERA_UPZ); //6,1,16,15,25,5,-1,-1,-1,
		disp();
		scores[0]->drawText(mowers[0]->getScore());
		glViewport(windowwidth/2,0.0,windowwidth/2,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight /2,1.0f,50.0f);	
		gluLookAt(-transX+mowers[1]->getRight(),-transY,-transZ+mowers[1]->getUp(),mowers[1]->getRight(),-mowers[1]->getUp(),0,LEVELLOOP_CAMERA_UPX,LEVELLOOP_CAMERA_UPY,LEVELLOOP_CAMERA_UPZ); //6,1,16,15,25,5,-1,-1,-1,
		disp();
		scores[1]->drawText(mowers[1]->getScore());
	} else {
		//For 3 player, split the window into quarters
		//TODO: Write code for 3 or 4 mowers
		//3 or 4 mowers
	}
	SDL_GL_SwapBuffers();
}
void LevelLoop::disp()
{	
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-5.0f);
		//Draw the field once
		field->render();
		//draw every mower on the field
		for(int i=0;i<=LEVELLOOP_MAXMOWERS - 1;i++) {
			if (mowers[i] != nullptr) {
				mowers[i]->draw();
			}
		}
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}
#endif