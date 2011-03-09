#include "levelloop.h"
int GameModeLoop::windowwidth;
int GameModeLoop::windowheight;
void LevelLoop::init()
{
	field = new GrassField(16);

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
		glTranslatef(-mowers[0]->getRight()/100.0f,mowers[0]->getUp()/100.0f,0);
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight /2,1.0f,50.0f);	
		//gluLookAt(eax,eay,eaz,cex,cey,cez,nx,ny,nz); //6,1,16,15,25,5,-1,-1,-1,
		disp();
		glViewport(windowwidth/2,0.0,windowwidth/2,windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glTranslatef(-mowers[1]->getRight()/100.0f,mowers[0]->getUp()/100.0f,0);
		gluPerspective(45.0f,(double)windowwidth / (double)windowheight /2,1.0f,50.0f);	
		disp();
	} else {
	
	}
		SDL_GL_SwapBuffers();
}
void LevelLoop::disp()
{
		//glViewport(0.0,0.0,windowwidth/2,windowheight);
	
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-5.0f);
		glRotatef(Yrot,1.0f,1.0f,0.0f);
		glRotatef(rotX,1.0,0.0,0.0); // Rotate on X
		glRotatef(rotY,0.0,1.0,0.0); // Rotate on Y
		glRotatef(rotZ,0.0,0.0,1.0); // Rotate on Y
		glTranslatef((transX),(transY),transZ); // Translate on X
		field->render();
		//landscape();//Draw Landscape and Grass
		//glTranslatef(0,0,0);
		//glScalef(0.1,0.1,0.1);
		//glTranslatef(4.0f,0,4.0f);
		//glRotatef(0,0,1,0);
		//glTranslatef(-4.0f,0,-4.0f);
		//drawModel(); //Draw Lawnmower
		for(int i=0;i<=3;i++) {
			if (mowers[i] != nullptr) {
				mowers[i]->draw();
			}
		}
	glLoadIdentity();
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);

	glEnd();
	glMatrixMode(GL_MODELVIEW);
}