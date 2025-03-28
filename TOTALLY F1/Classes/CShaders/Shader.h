#pragma once

#include <fstream>
#include <sstream>
#include "../../Config/namespace.h"

/*	This is the Shader class
		- Deals with loading, creating, attaching, and linking the shaders
		- Main purpose is to create the vertex and fragment shader for the object
		- It also stores the shader program of the object, which is then accessed via getShaderProg()

	[Created by: Yza Montuerto]
*/
class Shader {
private:
	//Holds the vertex, fragment, and shader program
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProg;

public:
	//CONSTRUCTOR
	Shader();

	//FUNCTION
	void createShader(string vertPath, string fragPath);

	//GETTER
	GLuint getShaderProg();
};