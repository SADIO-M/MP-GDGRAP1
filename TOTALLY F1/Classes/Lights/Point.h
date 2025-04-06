#pragma once

#include "Light.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/*
	This is the Point class
		- Contains all of the necessary information for a point light
		- This point light was mainly used for the signal lights at the start of the game
		- Child of Light
		- This is a parent of the Spot light, since both are essentially the same except the spot light has a cone

	[Created by: Megan Sadio]
*/
class Point : public Light {
protected:
	// Modifiers for attenuation, determines the light fall-off
	float quadMod;
	float linearMod;
	float constantMod;
	
public:
	//CONSTRUCTORS
	Point();
	Point(vec3 position, vec3 color,
		float ambStr, float specStr, float specPhong,
		float brightness,
		float quadratic, float linear, float constant);

	//FUNCTIONS
	virtual void loadPoint(GLuint shaderProg, string lightType);
	virtual void updatePointLight(POINT_LIGHT_COLOR light);
};