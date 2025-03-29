#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "Model3D.h"
#include "../TextureMaker/TextureMaker.h"

/*
	Class for the kart (car) object.
		- Contains all functions necessary for the cart model parts
		- Slightly different from the LightBall object because it has a texture
		- child of Model3D

	[Created by: Megan Sadio & Yza Montuerto]
*/
class Kart : public Model3D {
private:
	vec3 kartPosMod;
	vec3 kartRotateMod;

	GLuint texture;
	TextureMaker textureMaker;

public:
	//CONSTRUCTOR
	Kart();
	Kart(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texPath);

	//FUNCTIONS
	void loadKart();
	void assignTexture();

	void transform();
	void draw();

	//GETTER
	GLuint getTexture();
};