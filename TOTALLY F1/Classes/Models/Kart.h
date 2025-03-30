#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "Model3D.h"
#include "../Cameras/Perspective.h"
#include "../TextureMaker/TextureMaker.h"

/*
	Class for the kart (car) object.
		- Contains all functions necessary for the cart model parts
		- Slightly different from the LightBall object because it has a texture
		- child of Model3D

	[Created by: Megan Sadio & Yza Montuerto]
*/
class Kart : public Model3D {
protected:
	float speed = 0.0f;
	float maxSpeed;
	float accelMod;
	float acceleration = 0.0f;
	float deceleration;

	vec3 direction = vec3(0.0f, 0.0f, 1.0f);

	bool isReversing = false;

	GLuint texture;
	TextureMaker textureMaker;

public:
	//CONSTRUCTOR
	Kart();
	Kart(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texPath,
		float maxSPD, float accelMod);

	//FUNCTIONS
	void loadKart();
	void assignTexture();

	virtual void update();
	virtual void draw();

	//GETTER
	GLuint getTexture();
	void setAcceleration(float newAcceleration);

	virtual void turn(float rotateY);
	virtual void setReverse(bool reverse);
};