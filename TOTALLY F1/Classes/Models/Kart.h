#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "Model3D.h"
#include "../Cameras/Perspective.h"
#include "../TextureMaker/TextureMaker.h"

/*
	Class for the kart (car) object.
		- Contains all functions necessary for the kart model parts
		- All three karts use this class, but the player's kart is a child of this (since it can steer)
		- Has movement and max speeds to allow for a faster / slower ghost karts
		- Also has transparency to allow two of the karts to be ghosts
		- Child of Model3D
		- Parent of PlayerKart, so it has inheritable variables and functions

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
	virtual void checkAtEnd();

	virtual void turn(float rotateY);
	virtual void update();
	virtual void draw();

	//GETTERS AND SETTERS
	virtual GLuint getTexture();
	virtual vec3 getDirection();
	virtual void setSpeed(float newSpeed);
	virtual void setAcceleration(float newAcceleration);
	virtual void setReverse(bool reverse);
	virtual void setGO(bool go);
	virtual bool getGO();
};