#include "Point.h"

//CONSTRUCTORS
Point::Point() {}

Point::Point(vec3 position, vec3 color,
	float ambStr, float specStr, float specPhong,
	float brightness,
	float quadratic, float linear, float constant) :
	Light(position, color, ambStr, specStr, specPhong, brightness) {

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

	GLuint quadAddress = glGetUniformLocation(shaderProg, (lightType + "quadMod").c_str());
	glUniform1f(quadAddress, quadMod);

	GLuint linearAddress = glGetUniformLocation(shaderProg, (lightType + "linearMod").c_str());
	glUniform1f(linearAddress, linearMod);

	GLuint constAddress = glGetUniformLocation(shaderProg, (lightType + "constantMod").c_str());
	glUniform1f(constAddress, constantMod);
}

/*
	This rotateLight function rotates the light based on the key pressed
		- This function is similar to the one found in Model3D, specifically updateRotation(char keyPressed)
*/
void Point::rotateLight(MOVE move) {
	switch (move) {
		case UP: lightPosition.x += rotateSpeed;
			break;
		case DOWN: lightPosition.x -= rotateSpeed;
			break;
		case RIGHT: lightPosition.y -= rotateSpeed;
			break;
		case LEFT: lightPosition.y += rotateSpeed;
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

void Point::updatePointLight(POINT_LIGHT_COLOR light) {
	vec3 newColor;
	float newAmbStr, newSpecStr, newSpecPhong, newBrightness;

	switch (light) {
	case NONE:
		newColor = vec3(0.0f, 0.0f, 0.0f);
		newAmbStr = 0.0f;
		newSpecStr = 0.0f;
		newSpecPhong = 0.0f;
		newBrightness = 0.0f;
		break;
	case RED:
		newColor = vec3(1.0f, 0.0f, 0.0f);
		newAmbStr = 2.0f;
		newSpecStr = 8.0f;
		newSpecPhong = 12.0f;
		newBrightness = 50.0f;
		break;
	case YELLOW:
		newColor = vec3(1.0f, 1.0f, 0.0f);
		newAmbStr = 2.0f;
		newSpecStr = 8.0f;
		newSpecPhong = 12.0f;
		newBrightness = 75.0f;
		break;
	case GREEN:
		newColor = vec3(0.0f, 1.0f, 0.0f);
		newAmbStr = 2.0f;
		newSpecStr = 8.0f;
		newSpecPhong = 12.0f;
		newBrightness = 100.0f;
		break;
	case WHITE:
		newColor = vec3(1.0f, 1.0f, 1.0f);
		newAmbStr = 0.3f;
		newSpecStr = 0.8f;
		newSpecPhong = 20.0f;
		newBrightness = 50.0f;
		break;
	}

	Light::updateLight(lightPosition, newColor, newAmbStr, newSpecStr, newSpecPhong, newBrightness);
}