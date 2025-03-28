#include "Point.h"

//CONSTRUCTORS
Point::Point() {}

Point::Point(vec3 position, vec3 color,
	float ambStr, float specStr, float specPhong,
	float brightness, float brightMod,
	float quadratic, float linear, float constant) :
	Light(position, color, ambStr, specStr, specPhong, brightness, brightMod) {

	initialPosition = lightPosition;
	quadMod = quadratic;
	linearMod = linear;
	constantMod = constant;
}

//FUNCTIONS
/*
	This loadPoint function is similar to loadDir, but it passes the quadMod, linearMod, and constantMod 
		- It also uses Light's loadLight function, since again, they are the same
*/
void Point::loadPoint(GLuint shaderProg, string lightType) {
	Light::loadLight(shaderProg, lightType);

	GLuint quadAddress = glGetUniformLocation(shaderProg, "quadMod");
	glUniform1f(quadAddress, quadMod);

	GLuint linearAddress = glGetUniformLocation(shaderProg, "linearMod");
	glUniform1f(linearAddress, linearMod);

	GLuint constAddress = glGetUniformLocation(shaderProg, "constantMod");
	glUniform1f(constAddress, constantMod);
}

/*
	updateColor updates the color of the light depending if its being controlled or not
		- Updates the light and ambient color
*/
void Point::updateColor(vec3 newColor) {
	lightColor = newColor;
	ambientColor = lightColor;
}

/*
	This rotateLight function rotates the light based on the key pressed
		- This function is similar to the one found in Model3D, specifically updateRotation(char keyPressed)
*/
void Point::rotateLight(char keyPressed) {
	switch (keyPressed) {
		case 'w': theta.x += rotateSpeed;
			break;
		case 's': theta.x -= rotateSpeed;
			break;
		case 'a': theta.y -= rotateSpeed;
			break;
		case 'd': theta.y += rotateSpeed;
			break;
	}

	// After it rotates the light, it updates its position
	updatePosition();
}

/*
	This update position function handles the light's movements
		- Since the light's movement is essentially a rotation, 
			all this does is rotate the light and update its position based on that rotation
*/
void Point::updatePosition() {
	lightRotation = rotate(mat4(1.0f), radians(theta.x), vec3(1, 0, 0));
	lightRotation = rotate(lightRotation, radians(theta.y), vec3(0, 1, 0));
	lightRotation = rotate(lightRotation, radians(theta.z), vec3(0, 0, 1));

	lightPosition = vec3(vec4(lightRotation * vec4(initialPosition, 1.0f)));
}