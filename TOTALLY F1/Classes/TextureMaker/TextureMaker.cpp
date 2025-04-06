#include "TextureMaker.h"

//CONSTRUCTOR
TextureMaker::TextureMaker() {}

//FUNCTION
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

void TextureMaker::makeTexCubeMap(GLuint* texture, string* faces, SELECT_TEXTURE texIndex) {
	glGenTextures(1, texture);
	setActiveTex(texIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *texture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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