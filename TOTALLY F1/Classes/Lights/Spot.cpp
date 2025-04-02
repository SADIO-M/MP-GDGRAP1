#include "Spot.h"

Spot::Spot(){ }

Spot::Spot(vec3 position, vec3 color,
	float ambStr, float specStr, float specPhong,
	float brightness,
	float quadratic, float linear, float constant,
	float outer, float inner, vec3 dir) :
	Point(position, color, ambStr, specStr, specPhong, brightness, quadratic, linear, constant) {

	outerCone = outer;
	innerCone = inner;
	spotDir = dir;
}

void Spot::loadSpot(GLuint shaderProg, string lightType) {
	Point::loadPoint(shaderProg, lightType);

	GLuint outerAddress = glGetUniformLocation(shaderProg, (lightType + "OuterCone").c_str());
	glUniform1f(outerAddress, outerCone);

	GLuint innerAddress = glGetUniformLocation(shaderProg, (lightType + "InnerCone").c_str());
	glUniform1f(innerAddress, innerCone);

	GLuint dirAddress = glGetUniformLocation(shaderProg, (lightType + "Dir").c_str());
	glUniform3fv(dirAddress, 1, value_ptr(spotDir));
}

void Spot::updateSpotPosDir(vec3 kartPos, vec3 kartDir) {
	mat4 rotationMatrix = rotate(mat4(1.0f), radians(theta.y), vec3(0.0f, 1.0f, 0.0f));
	vec3 offsetRotate = vec3(rotationMatrix * vec4(initialPosition, 1.0f));

	vec3 newLightPos = kartPos + offsetRotate;
	lightPosition = newLightPos;
	spotDir = kartDir;
}

void Spot::spotSpin(MOVE move) {
	switch (move) {
	case LEFT: theta.y += turnSpeed;
		break;
	case RIGHT: theta.y -= turnSpeed;
		break;
	}
}