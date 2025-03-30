#include "LightBall.h"

// Functions all similar to those in Kart.cpp

//CONSTRUCTORS
LightBall::LightBall(){}
LightBall::LightBall(string name, string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	vec3 color, vec3 pivot) :

	Model3D(name, pathName, pos, scale, rotate, vertPath, fragPath) {

	ballColor = color;  // Sets the color of the ball
    pivotPoint = pivot; // Sets the pivot point (where it rotates around)

    loadBall();         // Loads the ball
}

//FUNCTIONS
//This loadBall is similar to loadKart, except it only loads one shape since the light ball only has one shape
void LightBall::loadBall() {
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
void LightBall::update(){
    // Because the light ball rotates around a pivot point, we have to calculate its rotation based on that pivot
    translateToOrigin = translate(identity_matrix, -pivotPoint);   // Get a mat4 that translates the object to the origin
    resetTranslate = translate(identity_matrix, pivotPoint);       // Get a mat4 that resets that translation

    // Rotate the object 
    newRotation = rotate(identity_matrix, radians(theta.x), normalize(vec3(1, 0, 0)));
    newRotation = rotate(newRotation, radians(theta.y), normalize(vec3(0, 1, 0)));
    newRotation = rotate(newRotation, radians(theta.z), normalize(vec3(0, 0, 1)));

    // The new transformation matrix is based on the reset translate, new rotation, then translation to origin
    // Applies the rotation to its position as if it were on the origin, then it resets the translation to move it back to its proper place
    transformation_matrix = resetTranslate * newRotation * translateToOrigin;

    // Translate then scale
    transformation_matrix = translate(transformation_matrix, position);
    transformation_matrix = scale(transformation_matrix, scaling);

    unsigned int transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformation_matrix));

    // Passes the color of the ball to shader program
    GLuint colorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "color");
    glUniform3fv(colorAddress, 1, value_ptr(ballColor));
}

// Draws the object
void LightBall::draw(){
    update();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
}

//GETTER & SETTER
vec3 LightBall::getColor() { return ballColor; }

// Allows the model's color to be altered from Game
void LightBall::setColor(vec3 newColor){
    ballColor = newColor;
}