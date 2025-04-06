#pragma once
 
#include "../../Config/namespace.h"

/*
	This is the Camera class, the parent of the Perspective camera
		- Contains all general camera variables, setters, and getters

	[Created by: Megan Sadio]
*/
class Camera {
protected:
	float windowWidth;
	float windowHeight;

	mat4 viewMatrix;
	mat4 projectionMatrix;
	
	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
	
	float zNear;
	float zFar;
	
	vec3 cameraPosition;
	mat4 cameraPosMatrix;

	vec3 cameraCenter;

	vec3 cameraRotation;
	mat4 cameraRotMatrix;

public:
	//CONSTRUCTOR
	Camera();
	Camera(float width, float height,
		   float near,  float far,
		   vec3 position, vec3 center, 
		   vec3 rotation);

	//GETTERS & SETTERS
	virtual mat4 getView();
	virtual mat4 getProjection();
	virtual void setPosMat(mat4 newPosMat);
};