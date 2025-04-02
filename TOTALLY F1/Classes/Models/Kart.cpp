#include "Kart.h"

//CONSTRUCTOR
Kart::Kart(){}
Kart::Kart(string name, string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	string texPath, float maxSPD, 
    float accelMod, float transparency) :
        // calls Model3D's constructor
	Model3D(name, pathName, pos, scale, rotate, vertPath, fragPath){

    maxSpeed = maxSPD;
    this->accelMod = accelMod;
    this->transparency = transparency;

    SELECT_TEXTURE texIndex;
    if      (modelName == "KART1") texIndex = LIVERY;
    else if (modelName == "KART2") texIndex = WHEEL;
    else if (modelName == "KART3") texIndex = COVER;
	textureMaker.makeTex2D(&texture, texPath, texIndex);

    loadKart();
}

//FUNCTIONS
/*
    Handles mesh and vertex data.
        - Also calls Model3D's loadObj() and setUpVBO()
*/
void Kart::loadKart() {
	Model3D::loadObj();

    // Changes index depending on Kart part
    // 0 -> Livery, 1 -> Wheel, 2 -> Wheel Covers
    int shapeNo = 0;
    if (modelName == "KART2") shapeNo = 1;
    else if (modelName == "KART3") shapeNo = 2;

    // shapes is a <shape_T> vector included in the Model3D class
    for (int i = 0; i < shapes[shapeNo].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[shapeNo].mesh.indices[i].vertex_index);
    }

    for (int i = 0; i < shapes[shapeNo].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[shapeNo].mesh.indices[i].vertex_index);
        tinyobj::index_t vData = shapes[shapeNo].mesh.indices[i];

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
    Assigns the appropriate texture according to the kart part, and passes that to the corresponding shader program
*/
void Kart::assignTexture() {
    GLuint chooseTexAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "selectTex");

    if (modelName == "KART1") {
        GLuint texAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texLivery");
        textureMaker.setActiveTex(LIVERY);
        glUniform1i(texAddress, LIVERY);
        glUniform1i(chooseTexAddress, LIVERY);
    }
    else if (modelName == "KART2") {
        GLuint texAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texWheel");
        textureMaker.setActiveTex(WHEEL);
        glUniform1i(texAddress, WHEEL);
        glUniform1i(chooseTexAddress, WHEEL);
    }
    else if (modelName == "KART3") {
        GLuint texAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texCover");
        textureMaker.setActiveTex(COVER);
        glUniform1i(texAddress, COVER);
        glUniform1i(chooseTexAddress, COVER);
    }

    glBindTexture(GL_TEXTURE_2D, texture);
}

void Kart::assignTransparency() {
    GLuint transparencyAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "transparency");
    glUniform1f(transparencyAddress, transparency);
}

// Handles model transformations 
void Kart::update() {
    if(GO){
        if(speed < maxSpeed)
            speed += acceleration; //Either +- 0.0002f
        if (speed >= maxSpeed)
            speed = maxSpeed; //Sets speed to max speed
  
        //DECELERATION WHEN NOT MOVING
        if (speed > 0.0f)
            speed -= accelMod * 0.1f;

        // There is a max acceleration for reversing as well
        // Half of max speed since we don't really want to reverse too far
        if (speed <= -maxSpeed * 0.5f && isReversing)
            speed = -maxSpeed * 0.5f;

        //ACCELERATE IT WHEN IT REVERSES (basically decelerate it but the other way since
        //i was moving backwards)
        if (speed <= 0.0f && !isReversing)
            speed += accelMod * 0.1f;

        acceleration = 0;
   
        position += direction * speed;
    }

    //Transformation
    transformation_matrix = translate(identity_matrix, position);

    transformation_matrix = scale(transformation_matrix, scaling);

    transformation_matrix = rotate(transformation_matrix, radians(theta.z), normalize(vec3(0, 0, 1)));
    transformation_matrix = rotate(transformation_matrix, radians(theta.y), normalize(vec3(0, 1, 0)));
    transformation_matrix = rotate(transformation_matrix, radians(theta.x), normalize(vec3(1, 0, 0)));

    unsigned int transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformation_matrix));
}

// Handles model drawing
void Kart::draw() {
    update();
    assignTexture();
    assignTransparency();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
}

//GETTER
GLuint Kart::getTexture() { return texture; }

vec3 Kart::getDirection() { return direction; }

void Kart::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void Kart::setAcceleration(float newAcceleration) {
    acceleration = newAcceleration;
}

void Kart::turn(float rotateY) {
    theta.y = rotateY;
}

void Kart::setReverse(bool reverse) {
    isReversing = reverse;
}

void Kart::setGO(bool go) {
    GO = go;
}