#ifndef GRASSFIELD_H
#define GRASSFIELD_H
#include "SDL.h"
#include "SDL_opengl.h"
/**
This class is the field and contains all of the information for the grass and field
**/
class GrassField
{
protected:
	int fieldsize; //Static Size of Field fieldsize X fieldsize
	int** grasscut;
	GLuint side_texture;
	GLuint ttop_texture;
	GLuint bot_texture;
	GLuint fmodelid;
	/**
	Builds the Model Display List on object initialization
	**/
	void buildModel();
public:
	//Creates a New Grassfield
	GrassField(int size)
	{
		fieldsize = size;
		grasscut[size+1][size+1];
		grasscut = new int*[fieldsize+1];
		for(int i = 0; i <=fieldsize+1;i++)
			grasscut[i] = new int[fieldsize+1];

		fmodelid = glGenLists(1);
		buildModel();	
		growGrass();
		
	}
	//Deletes a Grassfield
	~GrassField()
	{
		for(int i=0;i<=fieldsize;i++) {
			delete [] grasscut[i];
		}
		delete[] grasscut;
		glDeleteTextures(1,&side_texture);
		glDeleteTextures(1,&ttop_texture);
		glDeleteTextures(1,&bot_texture);
		glDeleteLists(fmodelid,1);
	}
	/***
	Gets the width and height of field
	@return int fieldsize
	***/
	int getFieldSize()
	{
		return fieldsize;
	}
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