#include "Camera.h"

//CONSTRUCTOR
Camera::Camera(){}
Camera::Camera(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 rotation) {

	windowWidth = width;
	windowHeight = height;

	zNear = near;
	zFar = far;

	cameraPosition = position;
	cameraCenter = center;
	cameraRotation = rotation;
}

//GETTERS AND SETTERS
mat4 Camera::getView() { return viewMatrix; }

mat4 Camera::getProjection() { return projectionMatrix; }

void Camera::setPosMat(mat4 newPosMat) {
	cameraPosMatrix = newPosMat;
}