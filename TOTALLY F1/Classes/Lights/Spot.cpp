#include "Spot.h"

//CONSTRUCTORS
Spot::Spot(){ }
Spot::Spot(vec3 position, vec3 color,
	float ambStr, float specStr, float specPhong,
	float brightness,
	float quadratic, float linear, float constant,
	float outer, float inner, vec3 dir) :
	Point(position, color, ambStr, specStr, specPhong, brightness, quadratic, linear, constant) {

	initialPosition = lightPosition;
	outerCone = outer;
	innerCone = inner;
	spotDir = dir;
}

//FUNCTIONS
/*
	This loadSpot is similar to the loadPoint or loadDir, but for spot lights specifically
*/
void Spot::loadSpot(GLuint shaderProg, string lightType) {
	Point::loadPoint(shaderProg, lightType);

	GLuint outerAddress = glGetUniformLocation(shaderProg, (lightType + "OuterCone").c_str());
	glUniform1f(outerAddress, outerCone);

	GLuint innerAddress = glGetUniformLocation(shaderProg, (lightType + "InnerCone").c_str());
	glUniform1f(innerAddress, innerCone);

	GLuint dirAddress = glGetUniformLocation(shaderProg, (lightType + "Dir").c_str());
	glUniform3fv(dirAddress, 1, value_ptr(spotDir));
}

/*
	This function updates the spot light's position and direction based on the player kart's
	position and direction (or where it is facing)
		- Since the player kart can rotate and move around, this function ensures the lights follow the kart
*/
void Spot::updateSpotPosDir(vec3 kartPos, vec3 kartDir) {
	//Calculate the rotation of the light in the y axis (since the car can only rotate in that axis as well)
	lightRotation = rotate(mat4(1.0f), radians(theta.y), vec3(0.0f, 1.0f, 0.0f));
	//Get the offset, since the light isn't at the center of the car, its located at its front
	vec3 offsetRotate = vec3(lightRotation * vec4(initialPosition, 1.0f));

	//Update the new position based on the kart's position and the offset
	lightPosition = kartPos + offsetRotate;
	//Update the spot light's direction to be facing the same direction as the kart
	spotDir = kartDir;
}

/*
	This function allows the spot light to turn/spin based on where the kart turns/spins
*/
void Spot::spotSpin(MOVE move) {
	switch (move) {
	case LEFT: theta.y += turnSpeed;
		break;
	case RIGHT: theta.y -= turnSpeed;
		break;
	}
}