#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/* This is the TextureMaker class
		- It is similar to the implementation in PC02, but now it just LOADS textures
		- It takes in the texture variable to store it in, then just assigns that variable all the necessary texture info
		- This was changed especially when something needs to load multiple textures, this can just be called to load the texture

	[Created by: Megan Sadio]
*/
class TextureMaker {
private:
	int imageWidth, imageHeight, colorChannels;
	unsigned char* textureBytes;
public:
	//CONSTRUCTOR
	TextureMaker();
	
	//FUNCTION
	void setActiveTex(SELECT_TEXTURE texIndex);
	void makeTex2D(GLuint* texture, string texPath, SELECT_TEXTURE texIndex);
	void makeTexCubeMap(GLuint* texture, string* faces, SELECT_TEXTURE texIndex);
};