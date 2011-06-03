#ifndef TEXTDISPLAY_CPP
#define TEXTDISPLAY_CPP
#include "textdisplay.h"
TextDisplay::TextDisplay(int x, int y, int size)
{
	TTF_Init();
	this->x = x;
	this->y = y;
	this->size = size;
	this->color.b = 255;
	this->color.g = 255;
	this->color.r = 255;
	this->viewportwidth = GameModeLoop::windowwidth;
	this->viewportheight = GameModeLoop::windowheight;
	font = TTF_OpenFont( TEXTDISPLAY_FONTPATH, size );
	this->textureid = 99; //set to 99 to say "texture hasn't been drawn yet"
}
TextDisplay::~TextDisplay()
{
	TTF_CloseFont(font);
	TTF_Quit();
}
void TextDisplay::setBackgroundColor(bool usecolor,GLfloat bgcolor[4])
{
	this->backgroundcolor = usecolor;
	for(int i=0;i<=3;i++)
		this->bgcolor[i] = bgcolor[i];
}
void TextDisplay::setColor(int r, int g, int b)
{
	this->color.b = b;
	this->color.g = g;
	this->color.r = r;
}
void TextDisplay::setViewportParameters(int viewportwidth, int viewportheight)
{
	this->viewportwidth = viewportwidth;
	this->viewportheight = viewportheight;
}
void TextDisplay::drawText(const char* msg)
{
	//Enable Texturing
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);

	//Get back on the 2D Plane
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,this->viewportwidth,this->viewportheight,0);

	//If the message has changed since the last drawtext, redraw the bitmap
	if(strcmp(msg,message) != 0) 
	{
		strcpy(message,msg);
		//Delete the previous texture if there is one
		if (this->textureid != 99) {
			glDeleteTextures(1, &this->textureid);
		}
		
		//Draw text to SDL surface
		SDL_Surface *Message = TTF_RenderText_Blended(font, msg, color);
		assert(Message != false);
		glGenTextures(1, &textureid);
		glBindTexture(GL_TEXTURE_2D, textureid); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels);

		//Get width and height of new bitmap
		texw=Message->w;
		texh=Message->h;
		
		SDL_FreeSurface(Message);
	}
	//Draw Quad with new bitmap textured to it onto screen
	glBindTexture(GL_TEXTURE_2D, textureid); 
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3d(x, y, 0);
	glTexCoord2d(1, 0); glVertex3d(x+texw, y, 0);
	glTexCoord2d(1, 1); glVertex3d(x+texw, y+texh, 0);
	glTexCoord2d(0, 1); glVertex3d(x, y+texh, 0);
	glDisable(GL_TEXTURE_2D);
		
	glEnd(); 

	//Take glmatrix off the stack to get back to 3D mode
	glMatrixMode(GL_PROJECTION);
		glPopMatrix();
}
#endif