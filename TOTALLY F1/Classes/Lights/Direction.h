#pragma once

#include "Light.h"
#include "../../Config/namespace.h"

/*
	This is the Direction class
		- Contains all of the necessary information for a direction light
		- Its only difference to the point light is that its direction is fixed no matter what
		- loadDir is a function that sends the light direction to the shader program
		- child of Light

	[Created by: Megan Sadio]
*/
class Direction : public Light {
private:
	vec3 lightDirection;
public:
	//CONSTRUCTORS
	Direction();
	Direction(vec3 position, vec3 color,
		float ambStr, float specStr, float specPhong,
		float brightness, vec3 newDir);

	//FUNCTIONS
	void loadDir(GLuint shaderProg, string lightType);
	void updateDirLight(vec3 newPos, vec3 newColor,
						float newAmbStr,
						float newSpecStr, float newSpecPhong,
						float newBrightness, vec3 newDir);
};
