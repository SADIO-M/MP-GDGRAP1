#include "Direction.h"

//CONSTRUCTORS
Direction::Direction(){}

Direction::Direction(vec3 position, vec3 color,
	float ambStr, float specStr, float specPhong,
	float brightness, float brightMod, vec3 newDir) :
	Light(position, color, ambStr, specStr, specPhong, brightness, brightMod) {

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
	