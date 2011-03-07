#ifndef MOWER_CPP
#define MOWER_CPP
#include "lawnmower.h"
Mower* Mower::mowers[4];
int Mower::count;
//const int GrassField::fieldsize; //Static Size of Field fieldsize X fieldsize
int GrassField::grasscut[GrassField::fieldsize+1][GrassField::fieldsize+1];
void Mower::processMovement(){
	this->lup += this->cony;
	this->lright += this->conx;
	//this rotation stuff is necessary
	if (conx != 0 || cony != 0) {

		if (conx == 0) {
			if (cony > 0) {
				lrotation = 180;
			} else {
				lrotation = 0;
			}
		} else if (cony == 0) {
			if (conx > 0) {
				lrotation = 270;
			} else {
				lrotation = 90;
			}
		} else {
			//some combination of both
			lrotation = atan((double)conx/cony) * 180/3.1415926;
			if (cony > 0) {
				lrotation += 180;
			}
		}
	}
	//rotX += conrotx;
	//rotY += conroty;
	checkCollision();
}

void Mower::checkCollision()
{
	if(lright < 0) {
		lright = 0;
	}
	if(lup < 0) {
		lup = 0;
	}
	if(lright > GrassField::fieldsize) {
		lright = GrassField::fieldsize;
	}
	if(lup > GrassField::fieldsize) {
		lup = GrassField::fieldsize;
	}
	GrassField::grasscut[(int)lright][(int)lup] = 1;
	if(GrassField::grasscut[(int)lright][(int)lup] == 0 ) {
		score++;
		GrassField::grasscut[(int)lright][(int)lup] = 1;
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
		cony += 0.5;
	else if(Event.keysym.sym == settings.movedown)
		cony -= 0.5;
	else if (Event.keysym.sym == settings.moveleft)
		conx += 0.5;
	else if (Event.keysym.sym == settings.moveright)
		conx -= 0.5;

	//if(Event.keysym.sym == reset) {
	//	growGrass();	
	//}
}

void Mower::handleKeyboardDown(SDL_KeyboardEvent Event)
{
	if (Event.keysym.sym == this->settings.movedown)
		this->cony += 0.5;
	if (Event.keysym.sym == this->settings.moveup)
		this->cony -= 0.5;

	if (Event.keysym.sym == this->settings.moveleft)
		this->conx -= 0.5;
	if (Event.keysym.sym == this->settings.moveright)
		this->conx += 0.5;
}

void Mower::handleJoystickAxis(SDL_JoyAxisEvent Event)
{	
	if (Event.axis == 0) {
		conx = Event.value /60000.0f;
		if(abs(conx) < 0.125) {conx = 0;}
	} else if(Event.axis == 1) {
		cony = Event.value /60000.0f;
		if(abs(cony) < 0.125) {cony = 0;}
	} else if(Event.axis == 3) {
		conrotx = Event.value / 60000.0f;
		if(abs(conrotx) < 0.125) {conrotx = 0;}
	} else if(Event.axis == 4) {
		conroty = Event.value / 60000.0f;
		if(abs(conroty) < 0.125) {conroty = 0;}
	}
}


#endif