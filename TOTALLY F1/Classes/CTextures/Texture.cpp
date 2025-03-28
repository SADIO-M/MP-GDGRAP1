#include "Texture.h"

//CONSTRUCTOR
Texture::Texture() {} 

//FUNCTION
/*
	This function is to create the texture
		- It loads the texture from the given texture path
		- Flips the image so the texture doesn't get messed up
		- Generates and binds the texture, and also sets the appropriate color channels
*/
void Texture::createTexture(string texPath) {
	// Flips on load
	stbi_set_flip_vertically_on_load(true);

	// Loads texture
	textureBytes = stbi_load(
		texPath.c_str(),
		&imageWidth,
		&imageHeight,
		&colorChannels,
		0
	);

	// Generate and bind the texture
	glGenTextures(1, &objTexture);
	glBindTexture(GL_TEXTURE_2D, objTexture);

	// If the color channels = 3 (RGB), then load with only RGB
	if (colorChannels == 3) {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			imageWidth,
			imageHeight,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			textureBytes
		);
	}
	// If the color channels = 3 (RGBA), then load RGBA
	// Allows any texture to be loaded as long as its either 3 or 4 color channels
	else if (colorChannels == 4) {
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA, 
			imageWidth,
			imageHeight,
			0, 
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			textureBytes
		);
	}
	
	// Generates the mipmap of the texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Clean up
	stbi_image_free(textureBytes);
}

//GETTER
GLuint Texture::getTexture() { return objTexture; }