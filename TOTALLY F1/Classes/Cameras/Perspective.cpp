#include "Perspective.h"

Perspective::Perspective(){}

Perspective::Perspective(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 rotation, float FOV,
	float rotSpeed, float radius) : 
	Camera(width, height, near, far, position, center, rotation) {
	
	fieldOfView = FOV;
	rotateSpeed = rotSpeed;
	cameraRadius = radius;
}

void Perspective::rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	cameraRotation.x += (prevMousePos->x - currMousePos->x) * rotateSpeed;
	cameraRotation.y += (currMousePos->y - prevMousePos->y) * rotateSpeed;
	prevMousePos->x = currMousePos->x;
	prevMousePos->y = currMousePos->y;
}

void Perspective::rotateWithKeys(MOVE move) {
	switch (move) {
	case UP:    cameraRotation.y -= rotateSpeed * 5;
		break;				   
	case DOWN:  cameraRotation.y += rotateSpeed * 5;
		break; 
	case LEFT:  cameraRotation.x += rotateSpeed * 5;
		break;
	case RIGHT: cameraRotation.x -= rotateSpeed * 5;
		break;
	}
}

void Perspective::checkRotation() {
	if (cameraRotation.y >  -2.0f) cameraRotation.y =  -2.0f;
	if (cameraRotation.y < -70.0f) cameraRotation.y = -70.0f;
}

void Perspective::updateThirdPers(vec3 position){
	float rotXRadians = radians(cameraRotation.x);
	float rotYRadians = radians(cameraRotation.y);
	float fromGround  = cos(rotYRadians) * cameraRadius;

	float newPosX = fromGround    * sin(rotXRadians) + cameraCenter.x;
	float newPosY = -cameraRadius * sin(rotYRadians) + cameraCenter.y;
	float newPosZ = fromGround    * cos(rotXRadians) + cameraCenter.z;

	cameraPosition = vec3(newPosX, newPosY, newPosZ);
	cameraCenter = position;
}

void Perspective::updateFirstPers(vec3 position, vec3 direction) {
	cameraPosition = position + vec3(0.0f, 1.5f, 0.5f);
	cameraCenter = cameraPosition + direction;
}

void Perspective::draw(GLuint shaderProg){
	viewMatrix = lookAt(cameraPosition, cameraCenter, worldUp);

	// Projection matrix is perspective
	projectionMatrix = perspective(
		radians(fieldOfView),
		windowHeight / windowWidth,
		zNear,
		zFar);

	// Passes values to shader program
	GLuint cameraPositionAddress = glGetUniformLocation(shaderProg, "cameraPosition");
	glUniform3fv(cameraPositionAddress, 1, value_ptr(cameraPosition));

	GLuint viewCamAddress = glGetUniformLocation(shaderProg, "camera_view");
	glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(viewMatrix));

	GLuint projectionAddress = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projectionMatrix));
}
