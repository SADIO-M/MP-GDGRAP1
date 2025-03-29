#include "Camera.h"

//CONSTRUCTOR
Camera::Camera(){}
Camera::Camera(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 positionMod, vec3 rotationMod) {

	windowWidth = width;
	windowHeight = height;
	
	zNear = near;
	zFar = far;
	
	camPosition = position;
	initialPosition = camPosition;
	camCenter = center;
	
	camPositionMod = positionMod;
	camRotationMod = rotationMod;
}

//FUNCTIONS
/*
	This update function handles the transformation of the camera
		- It is also responsible for calculating the forward, right, and up vectors
		- Since all the camera's movement is essentially rotation (like the light), its transfomration is mainly rotations
*/
void Camera::update() {
	updatePosition();
	updateRotation();
	updateCenter();
}

void Camera::updatePosition() {
	camPosition = vec3(initialPosition.x + camPositionMod.x, initialPosition.y, initialPosition.z + camPositionMod.z);
	camCenter = vec3(0 + camPositionMod.x, 0, 0 + camPositionMod.z);
}

void Camera::updateRotation() {
	// Update F, R, U vectors
	forward = vec3(camCenter - camPosition);
	right = cross(forward, worldUp);
	up = cross(right, forward);

	// Rotate the camera accordingly 
	camRotationMatrix = rotate(identity_matrix, radians(camRotationMod.z), vec3(0, 0, 1));
	camRotationMatrix = rotate(camRotationMatrix, radians(camRotationMod.y), vec3(0, 1, 0));
	camRotationMatrix = rotate(camRotationMatrix, radians(camRotationMod.x), vec3(1, 0, 0));

	forward = vec3(camRotationMatrix * vec4(forward, 0.0f));
	right = vec3(camRotationMatrix * vec4(right, 0.0f));
	up = vec3(camRotationMatrix * vec4(up, 0.0f));
}



void Camera::updateCenter() {
	camCenter = camPosition + forward;
}

//GETTERS
mat4 Camera::getView() { return viewMatrix; }

mat4 Camera::getProjection() { return projectionMatrix; }