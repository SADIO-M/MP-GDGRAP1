#include "Direction.h"

//CONSTRUCTORS
Direction::Direction(){}
Direction::Direction(vec3 position, vec3 color,
	float ambStr, float specStr, float specPhong,
	float brightness, vec3 newDir) :
	Light(position, color, ambStr, specStr, specPhong, brightness) {

	lightDirection = newDir;
}

//FUNCTIONS
/*
	This loadDir function calls the loadLight function from the Light class (since it is essentially the same),
		but it also loads the light direction and passes that to the shader program
*/
void Direction::loadDir(GLuint shaderProg, string lightType){
	Light::loadLight(shaderProg, lightType);

	GLuint lightDirAddress = glGetUniformLocation(shaderProg, "direction");
	glUniform3fv(lightDirAddress, 1, value_ptr(lightDirection));
}

/*
	Updates the direction light color, intensity, and other variables based on if its morning or night
*/
void Direction::updateDirLight(SELECT_TEXTURE time){
	vec3 newPos, newColor, newDir;
	float newAmbStr, newSpecStr, newSpecPhong, newBrightness;
	
	switch (time) {
	//Night time direction light
	case NIGHT:
			newPos = vec3(-4.0f, 12.0f, 25.0f);
			newColor = vec3(1.0f, 1.0f, 1.0f);
			newAmbStr = 0.5f;
			newSpecStr = 2.0f;
			newSpecPhong = 10.0f;
			newBrightness = 0.6f;
			newDir = vec3(-4.0f, 12.0f, 25.0f);
		break;
	//Change direction light to look like the morning
	case MORNING:
			newPos = vec3(5.0f, 15.0f, 20.0f);
			newColor = vec3(0.9f, 1.0f, 0.9f);
			newAmbStr = 1.0f;
			newSpecStr = 5.0f;
			newSpecPhong = 15.0f;
			newBrightness = 1.0f;
			newDir = vec3(5.0f, 15.0f, 20.0f);
		break;
	}

	//Sends it to update light, since the other light children classes (point, spot) changes as well
	Light::updateLight(newPos, newColor, newAmbStr, newSpecStr, newSpecPhong, newBrightness);
	//Updates direction to new direction (because in the skybox, the sun and moon are positioned differently, 
	//	so at least it looks accurate
	lightDirection = newDir;
}
	