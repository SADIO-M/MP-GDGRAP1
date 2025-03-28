#include "Camera.h"

//CONSTRUCTOR
Camera::Camera(){}
Camera::Camera(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 rotationMod) {

	windowWidth = width;
	windowHeight = height;
	
	zNear = near;
	zFar = far;
	
	camPosition = position;
	initialPosition = camPosition; // Initial position saves the camera position when constructed
	camCenter = center;

	camRotationMod = rotationMod;
}

//FUNCTIONS
/*
	This update function handles the transformation of the camera
		- It is also responsible for calculating the forward, right, and up vectors
		- Since all the camera's movement is essentially rotation (like the light), its transfomration is mainly rotations
*/
void Camera::update() {
	// Update F, R, U vectors
	forward = vec3(camCenter - camPosition);
	right = cross(forward, worldUp);
	up = cross(right, forward);

	// Rotate the camera accordingly 
	camRotationMatrix = rotate(identity_matrix, radians(camRotationMod.z), vec3(0, 0, 1));
	camRotationMatrix = rotate(camRotationMatrix, radians(camRotationMod.y), vec3(0, 1, 0));
	camRotationMatrix = rotate(camRotationMatrix,   radians(camRotationMod.x), vec3(1, 0, 0));

	// Updates the camera's position from its rotation and its initial position
	//		- Saving this initial position is important especially for the Orthographic camera since it doesn't move
	//		- The perspective camera also needs its initial position for it to rotate properly
	camPosition = vec3(vec4(camRotationMatrix * vec4(initialPosition, 1.0f)));
}

//GETTERS
mat4 Camera::getView() { return viewMatrix; }

mat4 Camera::getProjection() { return projectionMatrix; }