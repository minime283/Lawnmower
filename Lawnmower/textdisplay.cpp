#include "textdisplay.h"
TextDisplay::~TextDisplay()
{
	TTF_Quit();
}
void TextDisplay::drawText(const char* msg)
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,this->viewportwidth,this->viewportheight,0);
	if(strcmp(msg,message) != 0) 
	{
		strcpy(message,msg);
		if (this->textureid != 99) {
			glDeleteTextures(1, &this->textureid);
		}
		TTF_Font *font;
		font = TTF_OpenFont( "../Assets/times.ttf", 25 );
		
		SDL_Surface *Message = TTF_RenderText_Blended(font, msg, color);
		assert(Message != false);
		glGenTextures(1, &textureid);
		glBindTexture(GL_TEXTURE_2D, textureid); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels);
		texw=Message->w;
		texh=Message->h;
		TTF_CloseFont(font);
		SDL_FreeSurface(Message);
	}
	glBindTexture(GL_TEXTURE_2D, textureid); 
	glBegin(GL_QUADS);
	//glDisable(GL_TEXTURE_2D);
	/*if(this->backgroundcolor) {
		glColor4fv(this->bgcolor);
		glVertex3d(x, y, -0.5);
		glVertex3d(x+texw, y, -0.5);
		glVertex3d(x+texw, y+texh, -0.5);
		glVertex3d(x, y+texh, -0.5);
	}*/
	//glEnable(GL_TEXTURE_2D);
	glTexCoord2d(0, 0); glVertex3d(x, y, 0);
	glTexCoord2d(1, 0); glVertex3d(x+texw, y, 0);
	glTexCoord2d(1, 1); glVertex3d(x+texw, y+texh, 0);
	glTexCoord2d(0, 1); glVertex3d(x, y+texh, 0);
	glDisable(GL_TEXTURE_2D);
		
	glEnd(); 

	glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	
	
	
}