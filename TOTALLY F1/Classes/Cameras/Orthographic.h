#pragma once

#include "Camera.h"
#include "../../Config/namespace.h"

/*
	This is the Orthographic class, it is an orthographic camera.
		- Contains all the variables needed for an orthographic camera
		- In the draw function, it makes its projection matrix = ortho(...)
		- Also holds the left, right, bottom, and top most points for the projection matrix
		- child of Camera

	[Created by: Megan Sadio]
*/

class Orthographic : public Camera {
private:
	float leftPoint;
	float rightPoint;
	float bottomPoint;
	float topPoint;

public:
	//CONSTRUCTORS
	Orthographic();
	Orthographic(float width, float height,
				 float near, float far,
				 vec3 position, vec3 center,
				 vec3 rotationMod, 
			     float left, float right, float bottom, float top);

	//FUNCTIONS
	void draw(GLuint shaderProg);
};