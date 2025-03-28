#pragma once

#include "Model3D.h"
#include "../../Config/namespace.h"

/*
	Class for the sphere of light object.
		- Contains all functions necessary for the ball/light model
		- Unlike Kart, does not contain a texture and instead has its own color
		- Since its rotation is also around a pivot point (the Kart, which is located at 0, 0, 0), it also has the location of that pivot
		- child of Model3D

	[Created by: Megan Sadio & Yza Montuerto]
*/
class LightBall : public Model3D {
private:
	vec3 ballColor;  // Color of the ball
	vec3 pivotPoint; // Pivot point of where it rotates around

	mat4 newRotation = mat4(1.0f); // Handles rotation
	mat4 translateToOrigin = mat4(1.0f); // Holds the translation to origin
	mat4 resetTranslate = mat4(1.0f);	// Holds the reset of the translation

public:
	//CONSTRUCTOR
	LightBall();
	LightBall(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		vec3 color, vec3 pivot);

	//FUNCTIONS
	void loadBall();

	void transform();
	void draw();

	//GETTER & SETTER
	vec3 getColor();
	void setColor(vec3 newColor);
};