#include "Orthographic.h"

//CONSTRUCTORS
Orthographic::Orthographic(){}

Orthographic::Orthographic(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 rotationMod,
	float left, float right, float bottom, float top):

	Camera(width, height, near, far,position, center, rotationMod) {

	leftPoint = left;
	rightPoint = right;
	bottomPoint = bottom;
	topPoint = top;
}

//FUNCTIONS
/*
	This draw function assigns the viewMatrix, projectionMatrix and passes the corresponding variables to the shader Program
		- The main difference between this and the perspective camera is that the projection matrix uses ortho (orthographic)
*/
void Orthographic::draw(GLuint shaderProg) {
	// View matrix to always look at the center
	viewMatrix = lookAt(camPosition, pivotPoint, worldUp);

	// Projection matrix is orthographic
	projectionMatrix = ortho(
		leftPoint,
		rightPoint,
		bottomPoint,
		topPoint,
		zNear,
		zFar);

	// Passes values to shader program
	GLuint cameraPositionAddress = glGetUniformLocation(shaderProg, "cameraPosition");
	glUniform3fv(cameraPositionAddress, 1, value_ptr(camPosition));

	GLuint viewCamAddress = glGetUniformLocation(shaderProg, "camera_view");
	glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(viewMatrix));

	GLuint projectionAddress = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projectionMatrix));
}