#pragma once

/*  This is a configurations file including all of the headers, namespaces and enumerations
       - Main purpose is ease of use especially for the namespaces
       - It also provides clarity via the enumerations for certain functions
*/

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef TINYOBJ_H
	#define TINYOBJ_H
	#define TINYOBJLOADER_IMPLEMENTATION
	#include "../../tiny_obj_loader.h"
#endif

#ifndef STB_H
	#define STB_H
	#include "../../stb_image.h"
#endif

using namespace std;
using namespace glm;
using namespace tinyobj;
