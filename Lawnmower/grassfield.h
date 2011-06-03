#ifndef GRASSFIELD_H
#define GRASSFIELD_H
#define GRASSFIELD_SIDETEXTURE "../Assets/side.bmp"
#define GRASSFIELD_TOPTEXTURE "../Assets/top.bmp"
#include "SDL.h"
#include "SDL_opengl.h"
/**
This class is the field and contains all of the information for the grass and field
**/
class GrassField
{
protected:
	int fieldsize; //Static Size of Field fieldsize X fieldsize
	/**
	total number of squares for this field
	**/
	int totalsquares;
	/**
	Total number of squares remaining
	**/
	int squaresremaining;
	/**
	2D array determining squares that are cut
	**/
	int** grasscut;
	/**
	Textures for the 3 sides of the field
	**/
	GLuint side_texture;
	GLuint ttop_texture;
	GLuint bot_texture;
	/**
	id for the display list
	**/
	GLuint fmodelid;
	/**
	Builds the Model Display List on object initialization
	**/
	void buildModel();
public:
	//Creates a New Grassfield
	GrassField(int size);
	//Deletes a Grassfield
	~GrassField();
	/***
	Gets the width and height of field
	@return int fieldsize
	***/
	int getFieldSize();
	/**
	Gets the total number of square
	**/
	int getTotalSquares();
	/**
	Gets the total number of squares remaining
	**/
	int getSquaresRemaining();
	/**
	Checks to see if grass is cut
	@param int x the x position to check
	@param int y the y position to check
	**/
	bool isGrassCut(int x, int y);
	/**
	Cuts the grass at this point
	@param int x the x position to cut
	@param int y the y position to cut
	**/
	void cutGrass(int x, int y);
	/**
		Renders the grassfield on every rende rcall
	**/
	void render();
	/**
	Regrows all grass on the field
	**/
	void growGrass();
};

#endif