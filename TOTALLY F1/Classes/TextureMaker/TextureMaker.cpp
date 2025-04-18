#include "TextureMaker.h"

//CONSTRUCTOR
TextureMaker::TextureMaker() {}

//FUNCTIONS
/*
	This function sets the active texture
		- Mainly for better tracking and setting active textures
		- Makes sure the correct texture is being set as active
*/
void TextureMaker::setActiveTex(SELECT_TEXTURE texIndex) {
	switch (texIndex) {
		case NIGHT:
			glActiveTexture(GL_TEXTURE0);
			break;
		case MORNING:
			glActiveTexture(GL_TEXTURE1);
			break;
		case LIVERY:
			glActiveTexture(GL_TEXTURE2);
			break;
		case WHEEL:
			glActiveTexture(GL_TEXTURE3);
			break;
		case COVER:
			glActiveTexture(GL_TEXTURE4);
			break;
		case TOWNHOUSE_COLOR:
			glActiveTexture(GL_TEXTURE5);
			break;
		case TOWNHOUSE_NORM:
			glActiveTexture(GL_TEXTURE6);
			break;
		case STONE_HOUSE_COLOR:
			glActiveTexture(GL_TEXTURE7);
			break;
		case STONE_HOUSE_NORM:
			glActiveTexture(GL_TEXTURE8);
			break;
	}
}

/*
	This function is to load the texture and place it in the passed GLuint* texture
		- It loads the texture from the given texture path
		- Flips the image so the texture doesn't get messed up
		- Generates and binds the texture, and also sets the appropriate color channels
*/
void TextureMaker::makeTex2D(GLuint* texture, string texPath, SELECT_TEXTURE texIndex) {
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
	glGenTextures(1, texture);
	setActiveTex(texIndex);
	glBindTexture(GL_TEXTURE_2D, *texture);

	//For normal mapping specifically, but it doesn't affect the other textures regardless
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

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

/*
	This function is to load the texture specifically for a skybox
		- It gets the texture, the array of strings for the faces, and where it will store (texIndex)
		- Generates the cube map texture for both the night and morning skyboxes
*/
void TextureMaker::makeTexCubeMap(GLuint* texture, string* faces, SELECT_TEXTURE texIndex) {
	//Generate, active and bind texture
	glGenTextures(1, texture);
	setActiveTex(texIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *texture);

	//Ensures smooth-looking sky
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//Loads the skybox faces
	for (GLuint i = 0; i < 6; i++) {
		stbi_set_flip_vertically_on_load(false);

		textureBytes = stbi_load(
			faces[i].c_str(),
			&imageWidth,
			&imageHeight,
			&colorChannels,
			0);

		if (textureBytes) {
			if (colorChannels == 3) {
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
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
			else if (colorChannels == 4) {
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
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

			stbi_image_free(textureBytes);
		}
	}

	stbi_set_flip_vertically_on_load(true);
}