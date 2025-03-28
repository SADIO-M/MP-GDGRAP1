#pragma once

#include "../../Config/namespace.h"

/* This is the Texture class
		- It is similar to the implementation in PC02, but now it just LOADS textures
		- It takes in the texture variable to store it in, then just assigns that variable all the necessary texture info
		- This was changed especially when something needs to load multiple textures, this can just be called to load the texture

	[Created by: Megan Sadio]
*/
class TextureLoader {
public:
	//CONSTRUCTOR
	TextureLoader();
	
	//FUNCTION
	void setActiveTex(SELECT_TEXTURE texIndex);
	void createTexture(GLuint* texture, string texPath, SELECT_TEXTURE texIndex);
};