#include "Building.h"

Building::Building(){}
Building::Building(string name, string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	string texColorPath, string texNormPath) : 

	Model3D(name, pathName, pos,  scale,  rotate, vertPath,  fragPath){

	//Texture here
    if (modelName == "TOWNHOUSE") {
        textureMaker.makeTex2D(&textureColor, texColorPath, TOWNHOUSE_COLOR);
    }
    else if (modelName == "STONE_HOUSE") {
        textureMaker.makeTex2D(&textureColor, texColorPath, STONE_HOUSE_COLOR);
    }

	loadBuilding();
}

void Building::loadBuilding(){
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

void Building::update(){
    transformation_matrix = translate(identity_matrix, position);
    transformation_matrix = scale(transformation_matrix, scaling);
    transformation_matrix = rotate(transformation_matrix, radians(rotation.x), vec3(1, 0, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.y), vec3(0, 1, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.z), vec3(0, 0, 1));

    unsigned int transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformation_matrix));
}

void Building::assignTexture(){
    GLuint texAddress;

    if(modelName == "TOWNHOUSE"){
        texAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texTownhouseColor");
        textureMaker.setActiveTex(TOWNHOUSE_COLOR);
        glUniform1i(texAddress, TOWNHOUSE_COLOR);
    }
    else if (modelName == "STONE_HOUSE") {
        texAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texStoneHouseColor");
        textureMaker.setActiveTex(STONE_HOUSE_COLOR);
        glUniform1i(texAddress, STONE_HOUSE_COLOR);
    }
 
    glBindTexture(GL_TEXTURE_2D, textureColor);
}

void Building::draw(){
    update();
    assignTexture();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
}