#pragma once

#include "../../Config/namespace.h"

/*
	This is the Light class, the parent class of Point and Direction
		- Contains the information needed by both light sources
		- It handles loading the lights (via passing it to the shader program) and adjusting its brightness

	[Created by: Megan Sadio]
*/

class Light {
protected:
	vec3 lightPosition;
	vec3 lightColor;

	float ambientStrength;
	vec3 ambientColor;

	float specularStrength;
	float specularPhong;

	float brightness;
	float brightMod; // Brightness modifier (value by which how much the brightness is modified)
public:
	//CONSTRUCTORS
	Light();
	Light(vec3 position, vec3 color,
		  float ambStr, float specStr, float specPhong,
		  float brightness, float brightMod);
	
	//FUNCTIONS
	virtual void loadLight(GLuint shaderProg, string lightType);
	virtual void adjustBrightness(ARROW_KEYS arrowPressed);
};
