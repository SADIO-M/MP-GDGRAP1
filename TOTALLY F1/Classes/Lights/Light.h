#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

/*
	This is the Light class, the parent class of Point, Direction, and Spot
		- Contains the information needed by all three light sources
		- It handles loading the lights (via passing it to the shader program)
		- It can also update the light information

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
public:
	//CONSTRUCTORS
	Light();
	Light(vec3 position, vec3 color,
		  float ambStr, float specStr, float specPhong,
		  float brightness);
	
	//FUNCTIONS
	virtual void loadLight(GLuint shaderProg, string lightType);
	virtual void updateLight(vec3 newPos, vec3 newColor,
							float newAmbStr,
							float newSpecStr, float newSpecPhong,
							float newBrightness);

};
