#pragma once
 
#include "../../Config/namespace.h"

/*
	This is the Camera class, the parent of Orthographic and Perspective
		- Contains all the variables and functions needed by both cameras
		- Handles its update and draw functions
			- The update function is for transformations
		- The draw function is required to be defined by its child classes

	[Created by: Megan Sadio]
*/

class Camera {
protected:
	float windowWidth;
	float windowHeight;

	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 identity_matrix = mat4(1.0f);

	vec3 forward;
	vec3 right;
	vec3 up;
	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);

	float zNear;
	float zFar;

	vec3 initialPosition;
	vec3 camPosition;
	vec3 camCenter;

	vec3 camPositionMod;
	vec3 camRotationMod; // Determines how much the camera has moved in its corresponding axis.
	mat4 camRotationMatrix = mat4(1.0f);

public:
	//CONSTRUCTORS
	Camera();
	Camera(float width, float height,
		   float near,  float far,
		   vec3 position, vec3 center,
		   vec3 positionMod, vec3 rotationMod);

	//FUNCTIONS
	virtual void update();
	virtual void updatePosition();
	virtual void updateRotation();
	virtual void updateCenter();

	virtual void draw(GLuint shaderProg) = 0;

	virtual mat4 getView();
	virtual mat4 getProjection();

	virtual void setPosMod(vec3 newPosMod);
};