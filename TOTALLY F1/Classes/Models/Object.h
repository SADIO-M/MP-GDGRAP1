#pragma once

#include "Model3D.h"
#include "../../Config/namespace.h"

/*
	This is the Object class
		- This class is for more "general" objects, like the plane and the signal light balls
		- Since both of them are just colored objects, this class handles both of them
		- It also allows color to change, specifically for the signal lights

	[Created by: Megan Sadio & Yza Montuerto]
*/
class Object : public Model3D {
private:
	vec3 color;  // Color of the object
public:
	//CONSTRUCTOR
	Object();
	Object(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		vec3 color);

	//FUNCTIONS
	void loadObject();

	void update();
	void draw();

	//GETTER & SETTER
	vec3 getColor();
	void setColor(vec3 newColor);
};