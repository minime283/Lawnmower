#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#define TEXTDISPLAY_FONTPATH "../Assets/times.ttf"
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
Object that draws the text (using a truetype font library) to a bitmap, 
and then uses the bitmap to texture a quad drawn onscreen.
**/
class TextDisplay{
public:
	/**
	@param int x the x position
	@param int y the y position
	@param int size the size (in pts) for the font
	**/
	TextDisplay(int x, int y, int size);
	~TextDisplay();
	/**
	@param int viewportwidth the viewport width
	@param int viewportheight the viewport height
	Sets custom viewport parameters
	**/
	void setViewportParameters(int viewportwidth, int viewportheight);
	/**
	@param bool usecolor use a background color
	@param GLfloat bgcolor the color to use (for glColor3fv function)
	**/
	void setBackgroundColor(bool usecolor,GLfloat bgcolor[4]);
	/**
	@param int r the red value
	@param int g the green value
	@param int b the blue value
	**/
	void setColor(int r, int g, int b);
	/**
	@param char* text
	**/
	void drawText(const char* text);
private:
	/**
	The TTF Font object
	**/
	TTF_Font *font;
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