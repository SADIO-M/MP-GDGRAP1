#pragma once

#include "Camera.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/*
	This is the Perspective class for the perspective camera
		- Contains all the variables needed for a perspective camera
		- Its main difference from the Orthographic camera is that it moves (rotates)
		- In the draw function, it makes its projection matrix = perspective(...)
		- Holds the field of view and rotation speed (since this camera rotates)
		- child of Camera

	[Created by: Megan Sadio]
*/

class Perspective : public Camera {
private:
	float fieldOfView;
	float FOVMod = 0.01f;

	float rotateSpeed = 0.008f;

public:
	//CONSTRUCTORS
	Perspective();
	Perspective(float width, float height,
		float near, float far,
		vec3 position, vec3 center,
		vec3 positionMod, vec3 rotationMod,
		float fov);

	//FUNCTIONS
	void rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos);
	void rotateWithKeys(MOVE move);
	void checkCameraRotation();

	void draw(GLuint shaderProg);
};