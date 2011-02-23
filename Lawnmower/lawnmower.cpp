#include "lawnmower.h"

//Method for position of grass, and if the grass has been cut
void growGrass(){
	int x,y;
	for(x=0;x<=fieldsize;x++) {
		for(y=0;y<=fieldsize;y++) {
			grasscut[x][y] = 0;
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
	//Textures being loaded from texture.cpp
	//Files are contained in data folder
	//side_texture = test.Loadbitmap("data/side.bmp");
	//top_texture = test.Loadbitmap("data/top.bmp");
	//bot_texture = test.Loadbitmap("data/bot.bmp");
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
		
		glGetFloatv(GL_CURRENT_COLOR,curColor);
		glLineWidth(3.0f);
		glColor3f(0,0,0);
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

		glEnd();
		glColor4fv(curColor);
	}
}
//Draws the lawnmower
void lawnmower(){
	int j=0;
	float x = 0;
	float y = 0;
	float z= 0;
	float plane = 0;
	glPushMatrix();
	//fix the orientation of the lawnmower
	glScalef(1.0,-1.0,1.0);
	glRotatef(90,1,0,0);
	glTranslatef(0,0,9);
	//draw the center rectangle
	glColor3f(0.0,1.0,0.0);	
	glPushMatrix();
		glScalef(1.0f,1.4f,0.6f);		
		glTranslatef(0.0f,0.0f,5.0f);
		drawCube(8);
	glPopMatrix();
	//draw the inner rectangle
	glColor3f(1.0,0.0,0.0);
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
		glColor3f(0.0,0.0,1.0);
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

	glPopMatrix();
	

}

void handleResize(int width, int height)
{
	glViewport(0.0,0.0,width,height);
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
	//int seed = 245;
	//seed the random function with an arbitrary constant (but still constant)
	//this allows the randomness of the field to NOT change on every render
	srand(245);
	//Like in the 3d Checkerboard cube we use 2 for loops
	for ( x = 0.0; x <= fieldsize; x += 1 ) {
	 for ( y = 0.0; y <= fieldsize; y += 1 ) {
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

		glBindTexture (GL_TEXTURE_2D, top_texture); //Final texture to be bound
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
				if (grasscut[(int)x][(int)y] == 0 && randomnumber < 0.75) {
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

		glTranslatef(lawnmowerright,0,lawnmowerup);
		glScalef(0.1,0.1,0.1);
		glTranslatef(4.0f,0,4.0f);
		glRotatef(lawnmowerrotation,0,1,0);
		glTranslatef(-4.0f,0,-4.0f);
		lawnmower(); //Draw Lawnmower
	SDL_GL_SwapBuffers();
}

void specialKey(unsigned char key, int x, int y) { 
// Check which key is pressed
	switch(key) {
		//Start Rotation Keys
		case 'a': // Rotates on x axis by -1 degree
			rotX -= 3.0;
		break;
		case 's': // Rotates on x axis by 1 degree
			rotX += 3.0;
		break;
		case 'q': // Rotates on y axis by -1 degree
			rotY -= 3.0;
		break;
		case 'w': // Rotates on y axis by 1 degree
			rotY += 3.0;
		break;
		case 'z': // Rotates on z axis by -1 degree
			rotZ -= 3.0; 
		break;
		case 'x': // Rotates on z axis by 1 degree
			rotZ += 3.0; 
		break;
		
		//Start Translations
		case 't': // Translates Left
			transX -= 1;
		break;
		case 'y': // Translates Right
			transX += 1;
		break;
		case 'g': // Down
			transY -= 1;
		break;
		case 'h': // Up
			transY += 1;
		break;
		case 'i': // Down
			transZ -= 1;
		break;
		case 'o': // Up
			transZ += 1;
		break;

	}
	//Debug:: Output coordinates of playing field
	//printf("transX:%f,transY:%ftransZ:%f\n",transX,transY,transZ);
	//printf("rotX:%f,rotY:%frotZ:%f\n",rotX,rotY,rotZ);
    //glutPostRedisplay(); // Redraw the scene
}

void processMouse(int button, int state, int x, int y) {
		/*if (button == GLUT_LEFT_BUTTON ) { //when left mouse button is pressed
			scaleX -= 0.10f; //Scale negative on x
			scaleY -= 0.10f; //Scale Negative on y 
			//It will increase it size on both x and y
			 //glScalef(scaleX, scaleY, 1.0);
		}
		else if (button == GLUT_RIGHT_BUTTON ) {
			scaleY += 0.10f; //Scale positive on X
			scaleX += 0.10f; // Scale positive on Y
			//It will increase it size on both x and y

			 //glScalef(scaleX, scaleY, 1.0);
		}*/
		// glutPostRedisplay(); // Redraw the scene
}
void checkCollision()
{
	if(lawnmowerright < 0) {
		lawnmowerright = 0;
	}
	if(lawnmowerup < 0) {
		lawnmowerup = 0;
	}
	if(lawnmowerright > fieldsize) {
		lawnmowerright = fieldsize;
	}
	if(lawnmowerup > fieldsize) {
		lawnmowerup = fieldsize;
	}
	grasscut[(int)lawnmowerright][(int)lawnmowerup] = 1;
}
//Begin Keyboard Controls
void processSpecial( SDL_keysym key){
	
	if(key.sym == movedown) {
		lawnmowerup += 0.5;		
		lawnmowerrotation = 180;
	}
	if(key.sym == moveup) {
		lawnmowerup -= 0.5;
		lawnmowerrotation = 0;
	}
	if(key.sym == moveright) {
		lawnmowerright += 0.5;
		lawnmowerrotation = 270;
	}
	if(key.sym == moveleft) {
		lawnmowerright -= 0.5;
		lawnmowerrotation = 90;
	}
	if(key.sym == reset) {
		growGrass();
		
	}
	checkCollision();
}

void processJoystiq(){
	checkCollision();
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
				processSpecial(Event.key.keysym);
				break;
		}
	}
	
}
int main(int argc, char** argv)
{

	SDL_Init(SDL_INIT_VIDEO);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	//SDL_Window window = SDL_CreateWindow("Lawnmower mowing the lawn.",300,100,750,550,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_SetVideoMode(640,480,16,SDL_OPENGL |SDL_DOUBLEBUF|SDL_HWSURFACE |SDL_RESIZABLE);
	//glutKeyboardFunc(specialKey); //Apply keyboard Control
	//glutSpecialFunc(processSpecial);
	//glutMouseFunc(processMouse);
	InitGL();
	//glutDisplayFunc(disp);
	//glutReshapeFunc(handleResize);
	//glutMainLoop();
	
	int prevclock = 0;
	int curclock = 0;
	handleResize(640,480);
	while(running) {
		checkevents();
		processJoystiq();
		disp();
	}
	//SDL_Quit();
	return 0;
}