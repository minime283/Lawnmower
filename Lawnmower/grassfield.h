#ifndef GRASSFIELD_H
#define GRASSFIELD_H
#include "SDL.h"
#include "SDL_opengl.h"
class GrassField
{
protected:
	int fieldsize; //Static Size of Field fieldsize X fieldsize
	int** grasscut;
	GLuint side_texture;
	GLuint ttop_texture;
	GLuint bot_texture;
	GLuint fmodelid;
	void buildModel();
public:
	//int grasscut[fieldsize+1][fieldsize+1];
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
	int getFieldSize()
	{
		return fieldsize;
	}
	bool isGrassCut(int x, int y);
	void cutGrass(int x, int y);
	void render();
	void growGrass();
};

#endif