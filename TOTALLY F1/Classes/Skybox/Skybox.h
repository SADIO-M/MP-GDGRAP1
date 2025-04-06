#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "../CShaders/Shader.h"
#include "../TextureMaker/TextureMaker.h"

/*
	This is the Skybox class
		- Handles all skybox-related things like setting up the cube VBO, EBO, and drawing

	[Created by: Yza Montuerto]
*/
class Skybox {
private:
	//Vertices of the cube
	float vertices[24] = {
		-1.f, -1.f,  1.f,	//0
		 1.f, -1.f,  1.f,	//1
		 1.f, -1.f, -1.f,	//2
		-1.f, -1.f, -1.f,	//3
		-1.f,  1.f,  1.f,	//4
		 1.f,  1.f,  1.f,   //5
		 1.f,  1.f, -1.f,	//6
		-1.f,  1.f, -1.f	//7
	};

	//Indices of the cube
	GLuint indices[36] = {
		1,2,6,
		6,5,1,

		0,4,7,
		7,3,0,

		4,5,6,
		6,7,4,

		0,3,2,
		2,1,0,

		0,1,5,
		5,4,0,

		3,7,6,
		6,2,3
	};

	mat4 skyView = mat4(1.0f);

	GLuint VBO;
	GLuint EBO;

	//TEXTURES
	GLuint morningTex;
	GLuint nightTex;

	Shader shaderMaker;
	TextureMaker textureMaker;
public:
	//CONSTRUCTORS
	Skybox();
	Skybox(string* nightFaces, string* morningFaces,
		string vertPath, string fragPath);

	//FUNCTIONS
	void setUpVBO();
	void setUpEBO();
	void draw(mat4 viewMatrix, mat4 projMatrix, SELECT_TEXTURE texIndex);
};