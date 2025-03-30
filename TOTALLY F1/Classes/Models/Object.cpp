#include "Object.h"

//CONSTRUCTORS
Object::Object(){}
Object::Object(string name, string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	vec3 color) :

	Model3D(name, pathName, pos, scale, rotate, vertPath, fragPath) {

	this->color = color;  
  
    loadObject();
}

//FUNCTIONS
//This loadBall is similar to loadKart, except it only loads one shape since the light ball only has one shape
void Object::loadObject() {
	Model3D::loadObj();

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[0].mesh.indices[i].vertex_index);
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);

        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);

        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
    }

	Model3D::setUpVBO();
}

/*
    Handles model transformations and color assignment.
*/
void Object::update(){
   
    transformation_matrix = translate(identity_matrix, position);
    transformation_matrix = scale(transformation_matrix, scaling);
    transformation_matrix = rotate(transformation_matrix, radians(rotation.x), vec3(1, 0, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.y), vec3(0, 1, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.z), vec3(0, 0, 1));

    unsigned int transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformation_matrix));

    // Passes the color of the ball to shader program
    GLuint colorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "color");
    glUniform3fv(colorAddress, 1, value_ptr(color));
}

// Draws the object
void Object::draw(){
    update();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
}

//GETTER & SETTER
vec3 Object::getColor() { return color; }

// Allows the model's color to be altered from Game
void Object::setColor(vec3 newColor){
    color = newColor;
}