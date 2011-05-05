#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <assert.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_opengl.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "gamemodeloop.h"

using namespace std;
/**
Displays the text
**/
class TextDisplay{
public:
	/**
	@param int viewportwidth the viewport width
	@param int viewportheight the viewport height
	Sets custom viewport parameters
	**/
	void setViewportParameters(int viewportwidth, int viewportheight)
	{
		this->viewportwidth = viewportwidth;
		this->viewportheight = viewportheight;
	}
	/**
	@param bool usecolor use a background color
	@param GLfloat bgcolor the color to use (for glColor3fv function)
	**/
	void setBackgroundColor(bool usecolor,GLfloat bgcolor[4])
	{
		this->backgroundcolor = usecolor;
		for(int i=0;i<=3;i++)
			this->bgcolor[i] = bgcolor[i];
	}
	/**
	@param int r the red value
	@param int g the green value
	@param int b the blue value
	**/
	void setColor(int r, int g, int b)
	{
		this->color.b = b;
		this->color.g = g;
		this->color.r = r;
	}
	/**
	@param int x the x position
	@param int y the y position
	@param int size the size (in pts) for the font
	**/
	TextDisplay(int x, int y, int size)
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
		this->textureid = 99;
		textureid = 0;
	}
	~TextDisplay();
	/**
	@param char* text
	**/
	void drawText(const char* text);
private:
	/**
	The texture for this textbox
	**/
	unsigned textureid;
	/**
	X position of the textbox
	**/
	int x;
	/**
	Y position of the textbox
	**/
	int y;
	/**
	Size (in pts) of the font
	**/
	int size;
	/**
	Color of the text
	**/
	SDL_Color color;
	/**
	Whether to use a background color
	**/
	bool backgroundcolor;
	/**
	Background color to use
	**/
	GLfloat bgcolor[4];
	/**
	Message to use
	**/
	char message[50];
	/**
	Texture height
	**/
	int texh;
	/**
	Texture width
	**/
	int texw;
	/**
	Viewport width
	**/
	int viewportwidth;
	/**
	Viewport height
	**/
	int viewportheight;
};
#endif