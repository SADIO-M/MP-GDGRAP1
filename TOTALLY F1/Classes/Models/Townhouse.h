#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "Model3D.h"
#include "../TextureMaker/TextureMaker.h"

class Townhouse : public Model3D {
private:
	GLuint textureColor;
	GLuint textureNormal;

	TextureMaker textureMaker;
public:
	Townhouse();
	Townhouse(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texColorPath, string texNormPath);

	void loadTownhouse();
	
	void update();
	void assignTexture();
	void draw();
};