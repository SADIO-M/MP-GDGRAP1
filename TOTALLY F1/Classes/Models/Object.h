#pragma once

#include "Model3D.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

class Object : public Model3D {
private:
	vec3 color;  // Color of the ball
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