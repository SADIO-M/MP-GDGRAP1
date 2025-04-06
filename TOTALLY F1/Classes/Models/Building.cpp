#include "Building.h"

//CONSTRUCTORS
Building::Building(){}
Building::Building(string name, string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	string texColorPath, string texNormPath) : 

	Model3D(name, pathName, pos,  scale,  rotate, vertPath,  fragPath){

	//Texture loading here
    //Since the two normally mapped objects have the same number of shapes and texture images,
    //this just checks which object it is and loads the corresponding textures
    if (modelName == "TOWNHOUSE") {
        textureMaker.makeTex2D(&textureColor, texColorPath, TOWNHOUSE_COLOR);
        textureMaker.makeTex2D(&textureNormal, texNormPath, TOWNHOUSE_NORM);
    }
    else if (modelName == "STONE_HOUSE") {
        textureMaker.makeTex2D(&textureColor, texColorPath, STONE_HOUSE_COLOR);
        textureMaker.makeTex2D(&textureNormal, texNormPath, STONE_HOUSE_NORM);
    }

	loadBuilding();
}

//FUNCTIONS
/*
    This loadBuilding function differentiates from the loadModel because its VBO settings are now different
        - It also loads all the shape data, including the position and uv of the points to allow normal mapping
*/
void Building::loadBuilding(){
	Model3D::loadObj();

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        meshIndices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    for (int i = 0; i < shapes[0].mesh.indices.size(); i+=3) {
        //Points of triangles
        index_t vDataNorms1 = shapes[0].mesh.indices[i];
        index_t vDataNorms2 = shapes[0].mesh.indices[i + 1];
        index_t vDataNorms3 = shapes[0].mesh.indices[i + 2];

        //Positions of points
            //POS 1
        vec3 pos1 = vec3(
            attributes.vertices[vDataNorms1.vertex_index * 3],
            attributes.vertices[vDataNorms1.vertex_index * 3 + 1],
            attributes.vertices[vDataNorms1.vertex_index * 3 + 2]
        );
        //POS 2
        vec3 pos2 = vec3(
            attributes.vertices[vDataNorms2.vertex_index * 3],
            attributes.vertices[vDataNorms2.vertex_index * 3 + 1],
            attributes.vertices[vDataNorms2.vertex_index * 3 + 2]
        );
        //POS 3
        vec3 pos3 = vec3(
            attributes.vertices[vDataNorms3.vertex_index * 3],
            attributes.vertices[vDataNorms3.vertex_index * 3 + 1],
            attributes.vertices[vDataNorms3.vertex_index * 3 + 2]
        );

        //UV of the points
            //UV 1
        vec2 uv1 = vec2(
            attributes.texcoords[vDataNorms1.texcoord_index * 2],
            attributes.texcoords[vDataNorms1.texcoord_index * 2 + 1]
        );
        //UV 2
        vec2 uv2 = vec2(
            attributes.texcoords[vDataNorms2.texcoord_index * 2],
            attributes.texcoords[vDataNorms2.texcoord_index * 2 + 1]
        );
        //UV 3
        vec2 uv3 = vec2(
            attributes.texcoords[vDataNorms3.texcoord_index * 2],
            attributes.texcoords[vDataNorms3.texcoord_index * 2 + 1]
        );

        //GETTING DELTA POSITION
        vec3 deltaPos1 = pos2 - pos1;
        vec3 deltaPos2 = pos3 - pos1;

        vec2 deltaUV1 = uv2 - uv1;
        vec2 deltaUV2 = uv3 - uv1;

        //REVERSE FACTOR
        float reverse = 1.0f /
            ((deltaUV1.x * deltaUV2.y) -
            (deltaUV1.y * deltaUV2.x));

        //COMPUTE TANGENT AND BITANGENT
        vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * reverse;
        vec3 biTan   = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * reverse;

        //PUSH DATA TO VECTOR ARRAY
        vec_Tangents.push_back(tangent);
        vec_Tangents.push_back(tangent);
        vec_Tangents.push_back(tangent);

        vec_BiTangents.push_back(biTan);
        vec_BiTangents.push_back(biTan);
        vec_BiTangents.push_back(biTan);
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
    
        //ADDED TANGENTS AND BI-TANGENTS TO THE FULL VERTEX DATA
        fullVertexData.push_back(vec_Tangents[i].x);
        fullVertexData.push_back(vec_Tangents[i].y);
        fullVertexData.push_back(vec_Tangents[i].z);

        fullVertexData.push_back(vec_BiTangents[i].x);
        fullVertexData.push_back(vec_BiTangents[i].y);
        fullVertexData.push_back(vec_BiTangents[i].z);
    }

    //Different VBO set up because of the added points
    setUpBuildingVBO();
}

/*
    This function sets up the VBO for the buildings
        - Since it has more vertex points, its VBO is set-up differently from the other models
*/
void Building::setUpBuildingVBO() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)0
    );

    GLintptr normPtr = 3 * sizeof(float);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)normPtr
    );

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)uvPtr
    );

    GLintptr tanPtr = 8 * sizeof(float);
    glVertexAttribPointer(
        3,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)tanPtr
    );

    GLintptr biTanPtr = 11 * sizeof(float);
    glVertexAttribPointer(
        4,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)biTanPtr
    );

    glEnableVertexAttribArray(0); //X, Y, Z
    glEnableVertexAttribArray(1); //Normals
    glEnableVertexAttribArray(2); //UVs
    glEnableVertexAttribArray(3); //Tangent
    glEnableVertexAttribArray(4); //BiTangent
}

/*
    Updates the building, and passes its transformation to the corresponding shader program
        - The usual implementation of passing the transformation
*/
void Building::update(){
    transformation_matrix = translate(identity_matrix, position);
    transformation_matrix = scale(transformation_matrix, scaling);
    transformation_matrix = rotate(transformation_matrix, radians(rotation.x), vec3(1, 0, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.y), vec3(0, 1, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.z), vec3(0, 0, 1));

    unsigned int transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformation_matrix));
}

/*
    Assigns the texture based on the building
        - If the building is the townhouse, assign the townhouse color and normal maps
        - Else, it assigns the stone house color and normal maps
        - Afterwards, it passes the corresponding textures to the shaders
*/
void Building::assignTexture(){
    GLuint texColorAddress;
    GLuint texNormalAddress;

    if(modelName == "TOWNHOUSE"){
        texColorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texTownhouseColor");
        textureMaker.setActiveTex(TOWNHOUSE_COLOR);
        glUniform1i(texColorAddress, TOWNHOUSE_COLOR);
    }
    else if (modelName == "STONE_HOUSE") {
        texColorAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texStoneHouseColor");
        textureMaker.setActiveTex(STONE_HOUSE_COLOR);
        glUniform1i(texColorAddress, STONE_HOUSE_COLOR);
    }
    glBindTexture(GL_TEXTURE_2D, textureColor);

    if (modelName == "TOWNHOUSE") {
        texNormalAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texTownhouseNormal");
        textureMaker.setActiveTex(TOWNHOUSE_NORM);
        glUniform1i(texNormalAddress, TOWNHOUSE_NORM);
    }
    else if (modelName == "STONE_HOUSE") {
        texNormalAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texStoneHouseNormal");
        textureMaker.setActiveTex(STONE_HOUSE_NORM);
        glUniform1i(texNormalAddress, STONE_HOUSE_NORM);
    }
    glBindTexture(GL_TEXTURE_2D, textureNormal);
}

/*
    Updates the building object, assigns its textures, then draws it
*/
void Building::draw(){
    update();
    assignTexture();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 14);
}