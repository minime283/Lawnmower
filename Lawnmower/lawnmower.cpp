#ifndef LAWNMOWER_CPP
#define LAWNMOWER_CPP
#include "lawnmower.h"
//Method for position of grass, and if the grass has been cut
void growGrass(){
	int x,y;
	for(x=0;x<=GrassField::fieldsize;x++) {
		for(y=0;y<=GrassField::fieldsize;y++) {
			GrassField::grasscut[x][y] = 0;
		}
	}
}
//Main OpenGL Routing 
void InitGL(){	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	growGrass();
	SDL_Surface* sur;

	sur = SDL_LoadBMP("../Assets/side.bmp");
	glGenTextures(1, &side_texture);
	glBindTexture( GL_TEXTURE_2D, side_texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D(GL_TEXTURE_2D,0,sur->format->BytesPerPixel,sur->w,sur->h,0,GL_RGB,GL_UNSIGNED_BYTE,sur->pixels);
	SDL_FreeSurface(sur);
	
	sur = SDL_LoadBMP("../Assets/top.bmp");
	glGenTextures(1, &ttop_texture);
	glBindTexture( GL_TEXTURE_2D, ttop_texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D(GL_TEXTURE_2D,0,sur->format->BytesPerPixel,sur->w,sur->h,0,GL_RGB,GL_UNSIGNED_BYTE,sur->pixels);
	SDL_FreeSurface(sur);
	
	sur = SDL_LoadBMP("../Assets/bot.bmp");
	glGenTextures(1, &bot_texture);
	glBindTexture( GL_TEXTURE_2D, bot_texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D(GL_TEXTURE_2D,0,sur->format->BytesPerPixel,sur->w,sur->h,0,GL_RGB,GL_UNSIGNED_BYTE,sur->pixels);
	SDL_FreeSurface(sur);
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
		
		//glMatrixMode(GL_COLOR);
		//glPushMatrix();
		//glMatrixMode(GL_MODELVIEW);
		//glGetFloatv(GL_CURRENT_COLOR,curColor);
		//glLineWidth(3.0f);
		/*glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex3f(0,0,plane );
			glVertex3f(size,0,plane);
			
			glVertex3f(size,0,plane);
			glVertex3f(size,size,plane);

			glVertex3f(size,size,plane);
			glVertex3f(0,0+size,plane);

			glVertex3f(0,0+size,plane);
			glVertex3f(0,0,plane );
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0,plane,0);
			glVertex3f(size,plane,0);

			glVertex3f(size,plane,0);
			glVertex3f(size,plane,size);

			glVertex3f(size,plane,size);
			glVertex3f(0,plane,size);

			glVertex3f(0,plane,size);
			glVertex3f(0,plane,0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(plane,0,0);
			glVertex3f(plane,size,0);

			glVertex3f(plane,size,0);
			glVertex3f(plane,size,size);

			glVertex3f(plane,size,size);
			glVertex3f(plane,0,size);

			glVertex3f(plane,0,size);
			glVertex3f(plane,0,0);

		glEnd();*/
		//glMatrixMode(GL_COLOR);
		//glPopMatrix();
		//glMatrixMode(GL_MODELVIEW);
		//glColor4fv(curColor);
	}
}


void handleResize(int width, int height)
{
	glViewport(0.0,0.0,width/2,height/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(double)width / (double)height,1.0f,50.0f);
}

/*
* Main playing field - Generates a X by Y field of cubes. 
* each smaller cube gets textured so when the playing field 
* increased it doesn't have a stretched squewed look.
*/
void landscape(){
	GLfloat  x,y,gx,gy;
	//seed the random function with an arbitrary constant (but still constant)
	//this allows the randomness of the field to NOT change on every render
	srand(245);
	//Like in the 3d Checkerboard cube we use 2 for loops
	for ( x = 0.0; x <= GrassField::fieldsize; x += 1 ) {
	 for ( y = 0.0; y <= GrassField::fieldsize; y += 1 ) {
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D); //Enable 2D texturing
		//Bind texture to the following polygons
		glBindTexture (GL_TEXTURE_2D, side_texture); 
		glBegin(GL_QUADS);// begin drawing our cube
		//  Points for texture mapping  Points for polygon creation
			glTexCoord2f(0 , 1);		glVertex3f(x, 1, y);
			glTexCoord2f(1 , 1);		glVertex3f(x+1, 1, y);
			glTexCoord2f(1 , 0);		glVertex3f(x+1, 0, y);
			glTexCoord2f(0 , 0);		glVertex3f(x, 0, y);

			//This is the back face
			glTexCoord2f(0 , 1);		glVertex3f(x, 1, y+1);
			glTexCoord2f(1 , 1);		glVertex3f(x+1, 1, y+1);
			glTexCoord2f(1 , 0);		glVertex3f(x+1, 0, y+1);
			glTexCoord2f(0 , 0);		glVertex3f(x, 0, y+1);

			//This is the left face
			glTexCoord2f(0 , 1);		glVertex3f(x, 1, y+1);
			glTexCoord2f(1 , 1);		glVertex3f(x, 1, y);
			glTexCoord2f(1 , 0);		glVertex3f(x, 0, y);
			glTexCoord2f(0 , 0);		glVertex3f(x, 0, y+1);

			//This is the right face
			glTexCoord2f(0 , 1);		glVertex3f(x+1, 1, y+1);
			glTexCoord2f(1 , 1);		glVertex3f(x+1, 1, y);
			glTexCoord2f(1 , 0);		glVertex3f(x+1, 0,   y);
			glTexCoord2f(0 , 0);		glVertex3f(x+1, 0, y+1);
		glEnd();

		glBindTexture (GL_TEXTURE_2D, bot_texture);// Next texture to be bound
		glBegin(GL_QUADS);
			//This is the bottom face
			glTexCoord2f(0 , 1);		glVertex3f(x, 0, y+1);
			glTexCoord2f(1 , 1);		glVertex3f(x, 0, y);
			glTexCoord2f(1 , 0);		glVertex3f(x+1, 0, y);
			glTexCoord2f(0 , 0);		glVertex3f(x+1, 0, y+1);
		glEnd();

		glBindTexture (GL_TEXTURE_2D, ttop_texture); //Final texture to be bound
		glBegin(GL_QUADS);
			//This is the top face
			glTexCoord2f(0 , 1);		glVertex3f(x, 1, y+1);
			glTexCoord2f(1 , 1);		glVertex3f(x, 1, y);
			glTexCoord2f(1 , 0);		glVertex3f(x+1, 1, y);
			glTexCoord2f(0 , 0);		glVertex3f(x+1, 1, y+1);
		glEnd(); //End Polygon
		glDisable(GL_TEXTURE_2D); //End Texturing

		//Begin Drawing Grass
		
		for ( gx = x; gx <= x+1; gx+=0.1) {
			for (gy = y; gy <= y+1; gy+=0.1) {
				//unfortunately, these random numbers must be generated, even if the grass is already cut in that area
				//this random number determines whether the grass will show up for this particular blade
				float randomnumber = (float)rand()/(float)RAND_MAX;
				//this random number determines how long the grass will show for this particular blade
				float randomnumber2 = (float)rand()/(float)RAND_MAX;
				if (GrassField::grasscut[(int)x][(int)y] == 0 && randomnumber < 0.75) {
						glColor3f(0.0f,1.0f,0.0f);
						//one triangle polygon to represent grass
						glBegin(GL_POLYGON);					
							glVertex3f(gx+0.05,1.0,gy+0.05);
							glVertex3f(gx+0.025, randomnumber2 * 1.55, gy+0.025);
							glVertex3f(gx, 1.0, gy);
						glEnd();				
				}
			}
		}
		
	  }
	}
}

//setup the landscape/grass/lawnmower and draw it
void disp(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-5.0f);
		glRotatef(Yrot,1.0f,1.0f,0.0f);
		glRotatef(rotX,1.0,0.0,0.0); // Rotate on X
		glRotatef(rotY,0.0,1.0,0.0); // Rotate on Y
		glRotatef(rotZ,0.0,0.0,1.0); // Rotate on Y
		glTranslatef((transX),(transY),transZ); // Translate on X
		
		landscape();//Draw Landscape and Grass
		//glTranslatef(0,0,0);
		//glScalef(0.1,0.1,0.1);
		//glTranslatef(4.0f,0,4.0f);
		//glRotatef(0,0,1,0);
		//glTranslatef(-4.0f,0,-4.0f);
		//drawModel(); //Draw Lawnmower
	Mower::drawAll();
		
	SDL_GL_SwapBuffers();
}








void checkevents()
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
				Mower::keyboardDown(Event.key);
				break;
			case SDL_KEYUP:
				Mower::keyboardUp(Event.key);
				break;
			case SDL_JOYAXISMOTION:
				Mower::joystickAxis(Event.jaxis);
				break;
		}
	}
	
}
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_Surface* screen = SDL_SetVideoMode(640,480,16,SDL_OPENGL |SDL_DOUBLEBUF|SDL_ANYFORMAT |SDL_RESIZABLE);
	InitGL();
	int prevclock = 0;
	int curclock = 0;
	handleResize(640,480);
	SDL_Joystick *joystick;
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	Mower* mowers[2];
	
	//mowers[0] = new Mower(SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT);
	//mowers[1] = new Mower(SDLK_w,SDLK_s,SDLK_a,SDLK_d);
	Mower::makeMower(0);
	Mower::makeMower(1);
	while(running) {
		curclock = clock();
		if (curclock - prevclock > 126) {
			checkevents();
			Mower::processMovementAll();
			disp();
		}	
	}
	SDL_Quit();
	return 0;
}
#endif