#include "grassfield.h"
//Method for position of grass, and if the grass has been cut
void GrassField::growGrass(){
	int x,y;
	for(x=0;x<=fieldsize;x++) {
		for(y=0;y<=fieldsize;y++) {
			grasscut[x][y] = 0;
		}
	}
}

void GrassField::buildModel(){
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

	glNewList(this->fmodelid,GL_COMPILE);
	GLfloat  x,y;
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
			glTexCoord2f(1 , 0);		glVertex3f(x, 1, y+1);
			glTexCoord2f(1 , 1);		glVertex3f(x, 1, y);
			glTexCoord2f(0 , 1);		glVertex3f(x, 0, y);
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
		
		
		
	  }
	}
	glEndList();
}

void GrassField::render(){
	GLfloat  x,y,gx,gy;
	//seed the random function with an arbitrary constant (but still constant)
	//this allows the randomness of the field to NOT change on every render
	srand(245);
	//Like in the 3d Checkerboard cube we use 2 for loops
	glCallList(this->fmodelid);
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);					
						
	//int counter = 0;
	for ( x = 0.0; x <= fieldsize; x += 1 ) {
	 for ( y = 0.0; y <= fieldsize; y += 1 ) {
		 for ( gx = x; gx <= x+1; gx+=0.2) {
			for (gy = y; gy <= y+1; gy+=0.2) {
				//unfortunately, these random numbers must be generated, even if the grass is already cut in that area
				//this random number determines whether the grass will show up for this particular blade
				//float randomnumber = (float)rand()/(float)RAND_MAX;
				//this random number determines how long the grass will show for this particular blade
				float randomnumber2 = (float)rand()/(float)RAND_MAX;
				if (GrassField::grasscut[(int)x][(int)y] == 0 ) {
						//one triangle polygon to represent grass
							glVertex3f(gx+0.05,1.0,gy+0.05);
							glVertex3f(gx+0.025, 1.0 + randomnumber2 * 0.55, gy+0.025);
							glVertex3f(gx, 1.0, gy);
				}
			}
		}
	 }
	}
	glEnd();				

}

bool GrassField::isGrassCut(int x, int y) {
	if (grasscut[x][y]==1) {
		return true;
	}
	return false;
}

void GrassField::cutGrass(int x, int y) {
	grasscut[x][y] = 1;
	this->squaresremaining--;
}