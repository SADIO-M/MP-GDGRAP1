#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "Model3D.h"
#include "../TextureMaker/TextureMaker.h"

/*
	This is the Building class
		- Responsible for handling the normally mapped landmarks
		- It is different from the other models because of its tangent and bi tangent vectors
		- It also has two textures for the color and normal
		- Aside from that, it loads the object like the other objects

	[Created by: Megan Sadio & Yza Montuerto]
*/
class Building : public Model3D {
private:
	//Vectors for tangent and bi-tangents for the normal mapping
	vector<vec3> vec_Tangents;
	vector<vec3> vec_BiTangents;

	//Texture to store the colored and normal textures
	GLuint textureColor;
	GLuint textureNormal;

	TextureMaker textureMaker;
public:
	//CONSTRUCTORS
	Building();
	Building(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texColorPath, string texNormPath);

	//FUNCTIONS
	void loadBuilding();
	void setUpBuildingVBO();
	
	void update();
	void assignTexture();
	void draw();
};