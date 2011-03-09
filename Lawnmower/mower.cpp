#ifndef MOWER_CPP
#define MOWER_CPP
#include "lawnmower.h"
Mower* Mower::mowers[4];
int Mower::count;
//const int GrassField::fieldsize; //Static Size of Field fieldsize X fieldsize
//int GrassField::grasscut[GrassField::fieldsize+1][GrassField::fieldsize+1];
void Mower::processMovement(){
	int curclock = clock();
	//Process Accelleration
	
	//Process Velocity
	this->lup += (curclock - this->last_update ) / 10 * this->vely;
	this->lright += (curclock - this->last_update) / 10 * this->velx;
	//this rotation stuff is necessary
	if (velx != 0 || vely != 0) {

		if (velx == 0) {
			if (vely > 0) {
				lrotation = 180;
			} else {
				lrotation = 0;
			}
		} else if (vely == 0) {
			if (velx > 0) {
				lrotation = 270;
			} else {
				lrotation = 90;
			}
		} else {
			//some combination of both
			lrotation = atan((double)velx/vely) * 180/3.1415926;
			if (vely > 0) {
				lrotation += 180;
			}
		}
	}
	//rotX += conrotx;
	//rotY += conroty;
	checkCollision();
	this->last_update = curclock;
}

//draws a 1x1 cube. Lawnmower is drawn entirely of these cubes (not including the wheels) (extorted of course)
void drawCube(int size){
	float plane=0;
	for(plane=0;plane<=size;plane+=size) {
		glBegin(GL_POLYGON);
			glVertex3f(0,0,plane );
			glVertex3f(size,0,plane);
			glVertex3f(size,size,plane);
			glVertex3f(0,0+size,plane);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(0,plane,0);
			glVertex3f(size,plane,0);
			glVertex3f(size,plane,size);
			glVertex3f(0,plane,size);
		glEnd();
		
		glBegin(GL_POLYGON);
			glVertex3f(plane,0,0);
			glVertex3f(plane,size,0);
			glVertex3f(plane,size,size);
			glVertex3f(plane,0,size);
		glEnd();
	}
}//draws a 1x1 cube. Lawnmower is drawn entirely of these cubes (not including the wheels) (extorted of course)
void Mower::drawCube(int size){
	float plane=0;
	for(plane=0;plane<=size;plane+=size) {
		glBegin(GL_POLYGON);
			glVertex3f(0,0,plane );
			glVertex3f(size,0,plane);
			glVertex3f(size,size,plane);
			glVertex3f(0,0+size,plane);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(0,plane,0);
			glVertex3f(size,plane,0);
			glVertex3f(size,plane,size);
			glVertex3f(0,plane,size);
		glEnd();
		
		glBegin(GL_POLYGON);
			glVertex3f(plane,0,0);
			glVertex3f(plane,size,0);
			glVertex3f(plane,size,size);
			glVertex3f(plane,0,size);
		glEnd();
	}
}

void Mower::checkCollision()
{
	if(lright < 0) {
		lright = 0;
	}
	if(lup < 0) {
		lup = 0;
	}
	if(lright > field->getFieldSize()) {
		lright = field->getFieldSize();
	}
	if(lup > field->getFieldSize()) {
		lup = field->getFieldSize();
	}
	if(field->isGrassCut((int)lright,(int)lup) == false ) {
		score++;
		field->cutGrass((int)lright,(int)lup);
	} else {
	}
}

void Mower::draw()
{
	glPushMatrix();
		glTranslatef(this->lright,0,this->lup);
		glTranslatef(0,0,0);
		glScalef(0.1,0.1,0.1);
		glTranslatef(4.0f,0,4.0f);
		glRotatef(this->lrotation,0,1,0);
		glTranslatef(-4.0f,0,-4.0f);
		glPushMatrix();
		drawModel(); //Draw Lawnmower
		glPopMatrix();
	glPopMatrix();
}
//Draws the lawnmower
void Mower::drawModel(){
	glCallList(this->modelid);
}
void Mower::initModel(){
	glNewList(this->modelid,GL_COMPILE);
	
	//fix the orientation of the lawnmower
	glScalef(1.0,-1.0,1.0);
	glRotatef(90,1,0,0);
	glTranslatef(0,0,9);
	//draw the center rectangle
	glColor4fv(settings.squarecol);	
	glPushMatrix();
		glScalef(1.0f,1.4f,0.6f);		
		glTranslatef(0.0f,0.0f,5.0f);
		drawCube(8);
	glPopMatrix();
	//draw the inner rectangle
	glColor4fv(settings.motorcol);
	glTranslatef(2,2,6);
	drawCube(4);

	//draw the four wheels
	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,0,1,0);
		glTranslatef(1.9f,0.6f,6.2f);
		//glutSolidTorus(0.7, 1.5, 10, 10);
		glTranslatef(0.0f,6.0f,0);
		//glutSolidTorus(0.7, 1.5, 10, 10);
		glTranslatef(0.0f,0.0f,-8.0f);
		//glutSolidTorus(0.7, 1.5, 10, 10);
		glTranslatef(0.0f,-6.0f,0);
		//glutSolidTorus(0.7, 1.5, 10, 10);
	glPopMatrix();
	//draw the handles
	glPushMatrix();
		glColor4fv(settings.handlecol);
		glRotatef(45,1,0,0);
		glTranslatef(-1.0,0.0f,-2.0f);
		glScalef(1,20,1);
		drawCube(1);
		glTranslatef(5.0f,0.0f,0.0f);
		drawCube(1);
		glTranslatef(-5.0f,1.0f,0.0f);
		glScalef(6.0f,1.0f/20.0f,1.0f);
		drawCube(1);
	glPopMatrix();

	
	glEndList();

}

void Mower::handleKeyboardUp(SDL_KeyboardEvent Event)
{
	if (Event.keysym.sym == settings.moveup)
		vely += 0.5;
	else if(Event.keysym.sym == settings.movedown)
		vely -= 0.5;
	else if (Event.keysym.sym == settings.moveleft)
		velx += 0.5;
	else if (Event.keysym.sym == settings.moveright)
		velx -= 0.5;

	//if(Event.keysym.sym == reset) {
	//	growGrass();	
	//}
}

void Mower::handleKeyboardDown(SDL_KeyboardEvent Event)
{
	if (Event.keysym.sym == this->settings.movedown)
		this->vely += 0.5;
	if (Event.keysym.sym == this->settings.moveup)
		this->vely -= 0.5;

	if (Event.keysym.sym == this->settings.moveleft)
		this->velx -= 0.5;
	if (Event.keysym.sym == this->settings.moveright)
		this->velx += 0.5;
}

void Mower::handleJoystickAxis(SDL_JoyAxisEvent Event)
{	
	if (Event.axis == 0) {
		velx = Event.value /60000.0f;
		if(abs(velx) < 0.125) {velx = 0;}
	} else if(Event.axis == 1) {
		vely = Event.value /60000.0f;
		if(abs(vely) < 0.125) {vely = 0;}
	} else if(Event.axis == 3) {
		conrotx = Event.value / 60000.0f;
		if(abs(conrotx) < 0.125) {conrotx = 0;}
	} else if(Event.axis == 4) {
		conroty = Event.value / 60000.0f;
		if(abs(conroty) < 0.125) {conroty = 0;}
	}
}


#endif

MowerSettings Mower::msettings[4] =
{{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1}
},
{
	SDLK_w,
	SDLK_s,
	SDLK_a,
	SDLK_d,
	{0,1,1,1},
	{1,1,0,1},
	{1,0,1,1}
},
{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
},
{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
	}};
