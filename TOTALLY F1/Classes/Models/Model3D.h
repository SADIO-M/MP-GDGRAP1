#pragma once

#include "../CShaders/Shader.h"
#include "../../Config/namespace.h"

/*
    The parent class of Kart and LightBall
        - Contains all information and functions required by both objects
        - The type of the allModels vector in Game
        - Loads the objects, sets up the VBOs and updates the rotation
        - The transform and draw are required to be defined by its child classes

    [Created by: Megan Sadio]
*/
class Model3D {
protected:
    string modelName;

    // Information required by all models
    string path;
    bool loadSuccess;
    vector<shape_t> shapes;
    vector<material_t> material;
    string warning, error;
    attrib_t attributes;
    vector<GLuint> meshIndices;
    vector<GLfloat> fullVertexData;

    // VBO of the object
    GLuint VBO;
    // Corresponding shaderProg that the object will use
    Shader shaderMaker;

    // For tranformations
    mat4 transformation_matrix;
    mat4 identity_matrix = mat4(1.0f);

    vec3 position;
    vec3 scaling;
    vec3 rotation;

    vec3 theta = vec3(0.0f);
    float rotateSpeed = 0.05;

public:
    //CONSTRUCTORS
    Model3D();
    Model3D(string name, string pathName,
        vec3 pos, vec3 scale, vec3 rotate,
        string vertPath, string fragPath);

    //FUNCTIONS
    virtual void loadObj();
    virtual void setUpVBO();

        // Requires definition in child classes
    virtual void update() = 0;
    virtual void draw() = 0;

    //GETTERS
    virtual string getName();
    virtual Shader getShader();
    virtual vec3 getPosition();
    
    //DECONSTRUCTOR
    ~Model3D();
};
