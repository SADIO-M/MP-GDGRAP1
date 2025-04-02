#pragma once

#include "Light.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/*
	This is the Point class
		- Contains all of the necessary information for a point
		- It is different to the direction light because:
			- It holds the initial position of the light (relevant for transformation)
			- It has attenuation (represented by the quadMod, linearMod, and constantMod variables)
			- It has a rotation via theta, rotation speed, and lightRotation
		- child of Light

	[Created by: Megan Sadio]
*/
class Point : public Light {
protected:
	vec3 initialPosition;

	// Modifiers for attenuation, determines the light fall-off
	float quadMod;
	float linearMod;
	float constantMod;

	// Light rotation matrix
	mat4 lightRotation = mat4(1.0f);

	// For the light's rotation since it can move
	vec3 theta = vec3(0.0f);
	float rotateSpeed = 0.05f;
	
public:
	//CONSTRUCTOR
	Point();
	Point(vec3 position, vec3 color,
		float ambStr, float specStr, float specPhong,
		float brightness,
		float quadratic, float linear, float constant);

	//FUNCTIONS
	virtual void loadPoint(GLuint shaderProg, string lightType);

	void rotateLight(MOVE move);
	void updatePosition();

	virtual void updatePointLight(POINT_LIGHT_COLOR light);
};