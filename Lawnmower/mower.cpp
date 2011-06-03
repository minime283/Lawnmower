#ifndef MOWER_CPP
#define MOWER_CPP
#include "mower.h"
Mower* Mower::mowers[4];
int Mower::count;
const float Mower::radius = 1.0f;
const float Mower::mass = 1.2f;
const float Mower::coeff = 0.99f;
Mower::Mower(int index)
{
	init(index);
}
Mower::~Mower()
{
	glDeleteLists(1,modelid);
}
GLfloat Mower::getUp()
{
	return this->lup;
}
void Mower::setUp(GLfloat up)
{
	this->lup = up;
}
GLfloat Mower::getRight()
{
	return this->lright;
}
void Mower::setRight(GLfloat right) 
{
	this->lright = right;
}
GLfloat Mower::getVelocityX()
{
	return this->velx;
}
GLfloat Mower::getVelocityZ()
{
	return this->velz;
}
void Mower::setVelocityX(GLfloat velx)
{
	this->velx = velx;
}
void Mower::setVelocityZ(float velz)
{
	this->velz = velz;
}
GLfloat Mower::getLastUp()
{
	return this->clast_up;
}
GLfloat Mower::getLastRight()
{
	return this->clast_right;
}
int Mower::getMIndex()
{
	return this->index;
}
MowerSettings Mower::getSettings()
{
	return settings;
}
void Mower::setField(GrassField *field)
{
	this->field = field;
}
void Mower::init(int index)
{
	last_update = 0;
	clast_update =0;
	modelid = glGenLists(1);
	this->index = index;
	settings = msettings[index];
	Mower::count++;
	initModel();
	score = 0;
	velx = 0.0f;
	velz = 0.0f;
	accx = 0.0f;
	accy = 0.0f;
	clast_up = settings.startup;
	clast_right = settings.startright;
	lup = settings.startup;
	lright =settings.startright;
	lrotation =0.0f;
	prevcol = false;
}
const char* Mower::getScore()
{
	sprintf(sscore,"%i (%i%c)",score,(int)((float)score/(float)this->field->getTotalSquares()*100),'%');
	return sscore;
}
int Mower::getNumScore()
{
	return score;
}
void Mower::processMovement(){
	int curclock = clock();
	int timepassed = curclock - this->last_update;
	this->last_update = curclock;
	if (timepassed == 0) { return; }
	//Process Accelleration
	this->velx *= pow(0.999,timepassed);
	this->velz *= pow(0.999,timepassed);
	for(int i =0; i<=timepassed;i++) {		
		if (this->velx >= this->settings.maxvelocity) {
			this->velx = this->settings.maxvelocity;
		} else {
			this->velx += this->accx / 1000;
		}
		if (this->velz >= this->settings.maxvelocity) {
			this->velz = this->settings.maxvelocity;
		} else {
			this->velz += this->accy / 1000;
		}
		//Process Velocity
		this->lup += this->velz / 10;
		this->lright += this->velx / 10;
		checkCollision();
		checkGrassCollision();
	}
	//rotate the lawnmower to the direction it is moving
	if (velx != 0 || velz != 0) {
		//complete right angles
		if (velx == 0) {
			if (velz > 0) {
				lrotation = 180;
			} else {
				lrotation = 0;
			}
		} else if (velz == 0) {
			if (velx > 0) {
				lrotation = 270;
			} else {
				lrotation = 90;
			}
		} else {
			//other angles
			lrotation = atan((double)velx/velz) * 180/3.1415926;
			if (velz > 0) {
				lrotation += 180;
			}
		}
	}
	
}

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
void Mower::updateLastCollisionCheck()
{
	clast_update = clock();
	clast_right = this->getRight();
	clast_up = this->getUp();
}
bool Mower::doMowersCollide(float m1up,float m1right,float m2up,float m2right)
{
	float distance = pow((float) pow(m1up - m2up,2) + pow(m1right-m2right,2),0.5f);
	if (distance < radius * 2) {
		return true;
	}
	return false;
}
void Mower::checkMowerCollision(Mower *othermower)
{
	//do a cheap collision detection using spheres.
	//creating a bounding volume around the lawnmowers, the sum of the radius
	//cannot be larger than the distance between the two radii.
	if(doMowersCollide(this->getUp(),this->getRight(),othermower->getUp(),othermower->getRight())) {
		//if previously in collision, do not process new collision until out of collision zone
		if (prevcol == true)
			return;
		float curlasttime = clast_update;
		float curtime = clock();
		float curup1;
		float curup2;
		float curright1;
		float curright2;
		bool iscol = true;
		float curpoint = 1.0f;
		//find point of collision through five iterations
		for(int i=0;(i<=5) || (i>5 && !iscol);i++) {
			if (iscol) {
			//back up half a step back
				curpoint /= 2;
			} else {
			//half a step forward
				curpoint += curpoint /2;
			}
			//get the up and right of both mowers at time of collision
			curup1 = this->getLastUp() + (this->getUp()-this->getLastUp())*curpoint;
			curup2 = othermower->getLastUp() + (othermower->getUp()-othermower->getLastUp())*curpoint;
			curright1 = this->getLastRight() + (this->getRight()-this->getLastRight())*curpoint;
			curright2 = othermower->getLastRight() + (othermower->getRight()-othermower->getLastRight())*curpoint;	
			//check to see if the mowers collide
			iscol = doMowersCollide(curup1,curright1,curup2,curright2);
		}
		//collision normal
		float collnormal[3] = {curright1-curright2,0,curup1-curup2};
		//move mowers to the point in which the collision started
		this->setUp(curup1);
		this->setRight(curright1);
		othermower->setUp(curup2);
		othermower->setRight(curright2);
		//Find the new velocities of the mowers
		float A = (mass * mass * (1+coeff) *
			((this->getVelocityX() - othermower->getVelocityX()*collnormal[0]) + 
			(this->getVelocityZ() - othermower->getVelocityZ()*collnormal[2])))
			/ (mass * 2);
		//apply new velocities of mowers to their current velocities
		this->setVelocityX(this->getVelocityX() + A * collnormal[0]);
		this->setVelocityZ(this->getVelocityZ() + A * collnormal[2]);
		othermower->setVelocityX(othermower->getVelocityX() - A * collnormal[0]);
		othermower->setVelocityZ(othermower->getVelocityZ() - A * collnormal[2]);
		//set this as the previous collison check
		this->last_update = clast_update + ((curtime-clast_update)*curpoint);
		prevcol = true;
	} else {
		prevcol = false;
	}
}
void Mower::checkGrassCollision()
{
	if(field->isGrassCut((int)(lright+0.5),(int)(lup+0.5)) == false ) {
		score++;
		field->cutGrass((int)(lright+0.5),(int)(lup+0.5));
	}	
}
void Mower::checkCollision()
{
	//check collision with boundaries
	if(lright < 0) {
		lright = 0;
		this->velx = -this->velx * 0.3;
	}
	if(lup < 0) {
		lup = 0;
		this->velz = -this->velz * 0.3;
	}
	if(lright > field->getFieldSize()) {
		lright = field->getFieldSize();
		this->velx = -this->velx * 0.3;
	}
	if(lup > field->getFieldSize()) {
		lup = field->getFieldSize();
		this->velz = -this->velz * 0.3;
	}	
}

void Mower::draw()
{
	glPushMatrix();
		glTranslatef(this->lright,0,this->lup);
		glTranslatef(0,0,0);
		glScalef(0.1,0.1,0.1);
		glTranslatef(4.0f,0,8.0f);
		glRotatef(this->lrotation,0,1,0);
		glTranslatef(-4.0f,0,-8.0f);
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
		this->accy += this->settings.acceleration;
	else if(Event.keysym.sym == settings.movedown)
		this->accy -= this->settings.acceleration;
	else if (Event.keysym.sym == settings.moveleft)
		this->accx += this->settings.acceleration;
	else if (Event.keysym.sym == settings.moveright)
		this->accx -= this->settings.acceleration;
}

void Mower::handleKeyboardDown(SDL_KeyboardEvent Event)
{
	if (Event.keysym.sym == this->settings.movedown)
		this->accy += this->settings.acceleration;
	if (Event.keysym.sym == this->settings.moveup)
		this->accy -= this->settings.acceleration;

	if (Event.keysym.sym == this->settings.moveleft)
		this->accx -= this->settings.acceleration;
	if (Event.keysym.sym == this->settings.moveright)
		this->accx += this->settings.acceleration;
}

void Mower::handleJoystickAxis(SDL_JoyAxisEvent Event)
{	
	if (Event.axis == 0) {
		this->accx = this->settings.acceleration /60000.0f;
		if(abs(velx) < 0.125) {velx = 0;}
	} else if(Event.axis == 1) {
		this->accy = this->settings.acceleration /60000.0f;
		if(abs(velz) < 0.125) {velz = 0;}
	}
}



//init the settings for each mower
MowerSettings Mower::msettings[4] =
{{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
	0.2,
	0.5,
	5.0,
	5.0
},
{
	SDLK_w,
	SDLK_s,
	SDLK_a,
	SDLK_d,
	{0,1,1,1},
	{1,1,0,1},
	{1,0,1,1},
	0.2,
	0.5,
	10.0,
	10.0
},
{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
	0.2,
	0.5,
	15.0,
	15.0
},
{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	{ 0,0,1,1 },
	{0,1,0,1},
	{1,0,0,1},
	0.2,
	0.5,
	20.0,
	20.0
}};
#endif