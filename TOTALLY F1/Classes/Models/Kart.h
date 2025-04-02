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

	float transparency;

	vec3 direction = vec3(0.0f, 0.0f, 1.0f);

	bool isReversing = false;
	bool GO = false;

	GLuint texture;
	TextureMaker textureMaker;

public:
	//CONSTRUCTOR
	Kart();
	Kart(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texPath,
		float maxSPD, float accelMod,
		float transparency);

	//FUNCTIONS
	void loadKart();
	void assignTexture();
	void assignTransparency();

	virtual void turn(float rotateY);
	virtual void update();
	virtual void draw();

	//GETTER
	virtual GLuint getTexture();
	virtual vec3 getDirection();
	virtual void setSpeed(float newSpeed);
	virtual void setAcceleration(float newAcceleration);
	virtual void setReverse(bool reverse);
	virtual void setGO(bool go);
};