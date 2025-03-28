#pragma once

#include "../../Config/namespace.h"

/* This is the Texture class
		- Main purpose is to generate textures
		- It stores the texture of the object and returns it
		- Mainly used in drawing the object, its so that the object gets drawn with its corresponding texture
		
	[Created by: Megan Sadio]
*/
class Texture {
private:
	int imageWidth, imageHeight, colorChannels; // Width, height, color channels of image
	unsigned char* textureBytes;				// Texture bytes
	GLuint objTexture;							// Where the texture is binded
public:
	//CONSTRUCTOR
	Texture();
	
	//FUNCTION
	void createTexture(string texPath);

	//GETTER
	GLuint getTexture();
};