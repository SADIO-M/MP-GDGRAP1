#include "Model3D.h"

//CONSTRUCTORS
Model3D::Model3D() {}
Model3D::Model3D(string name, string pathName, 
    vec3 pos, vec3 scale, vec3 rotate,
    string vertPath, string fragPath) {
        modelName = name;
        path = pathName;

        position = pos;
        scaling = scale;
        rotation = rotate;

        shaderMaker.createShader(vertPath, fragPath); // Makes the object's shader (See CShaders/Shader.h and .cpp)

        theta = rotate;
}

//FUNCTIONS
void Model3D::loadObj() {
    loadSuccess = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );
}

//Sets up the object's VBO 
void Model3D::setUpVBO() {
    // Generates the VBO
    glGenBuffers(1, &VBO);

    // Binds the VBO to whichever active VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // VBO Data
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    // X Y Z attributes
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    // Normal attributes
    GLintptr normPtr = 3 * sizeof(float);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)normPtr
    );

    // UV attributes
    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)uvPtr
    );

    // Enables the attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Unbind VBO for clean up
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Handles object rotation. Called in Game
void Model3D::updateRotation(char keyPressed) {
    switch (keyPressed) {
        case 'w': theta.x += rotateSpeed;
            break;
        case 's': theta.x -= rotateSpeed;
            break;
        case 'a': theta.y -= rotateSpeed;
            break;
        case 'd': theta.y += rotateSpeed;
            break;
    }
}

//GETTERS
string Model3D::getName() { return modelName; }

Shader Model3D::getShader() { return shaderMaker; }

vec3 Model3D::getPosition() { return position; }

//DECONSTRUCTOR
Model3D::~Model3D() {
    glDeleteBuffers(1, &VBO);
}

