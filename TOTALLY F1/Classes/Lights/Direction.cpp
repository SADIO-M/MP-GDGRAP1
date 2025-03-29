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

void Direction::updateDirLight(vec3 newPos, vec3 newColor,
	float newAmbStr,
	float newSpecStr, float newSpecPhong,
	float newBrightness, vec3 newDir) {

	Light::updateLight(newPos, newColor, newAmbStr, newSpecStr, newSpecPhong, newBrightness);

	lightDirection = newDir;

}
	