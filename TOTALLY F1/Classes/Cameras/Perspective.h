#pragma once

#include "Camera.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/*
	This is the Perspective class for the perspective camera
		- Contains all the variables needed for a perspective camera
		- It can also move around the player (if it is third person), and follows the player accordingly
		- Child of Camera

	[Created by: Megan Sadio]
*/
class Perspective : public Camera {
private:
	float fieldOfView;
	//Rotation speed and camera radius for the third person camera, since it can move
	float rotateSpeed;
	float cameraRadius;

public:
	//CONSTRUCTORS
	Perspective();
	Perspective(float width, float height,
		float near, float far,
		vec3 position, vec3 center,
		vec3 rotation, float FOV,
		float rotSpeed, float radius);

	//FUNCTIONS
	void rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos);
	void rotateWithKeys(MOVE move);
	void checkRotation();

	void updateThirdPers(vec3 position);
	void updateFirstPers(vec3 position, vec3 direction);

	void draw(GLuint shaderProg);
};