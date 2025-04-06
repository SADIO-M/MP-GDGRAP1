#pragma once

#include "Point.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/*
	This is the Spot class
		- Contains all of the necessary information for a spot light, specifically the outer and inner cones
		- Used as the headlights for the player kart
		- Grandchild of Light, and child of Point
		
	[Created by: Megan Sadio]
*/
class Spot : public Point {
private:
	//Initial position for movement-related calculations
	vec3 initialPosition;

	//Outer cone and inner cone of the light
	float outerCone;
	float innerCone;

	//Spot light direction since it moves along with the kart
	vec3 spotDir;

	// Light rotation matrix
	mat4 lightRotation = mat4(1.0f);

	// For the light's rotation since it can rotate
	vec3 theta = vec3(0.0f);
	float turnSpeed = 0.0375f;
public:
	//CONSTRUCTORS
	Spot();
	Spot(vec3 position, vec3 color,
		float ambStr, float specStr, float specPhong,
		float brightness,
		float quadratic, float linear, float constant,
		float outer, float inner, vec3 dir);

	//FUNCTIONS
	void loadSpot(GLuint shaderProg, string lightType);
	void updateSpotPosDir(vec3 kartPos, vec3 kartDir);
	void spotSpin(MOVE move);
};