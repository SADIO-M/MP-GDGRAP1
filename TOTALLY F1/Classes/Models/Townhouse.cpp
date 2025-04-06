#include "Townhouse.h"

Townhouse::Townhouse(){}
Townhouse::Townhouse(string name, string pathName,
	vec3 pos, vec3 scale, vec3 rotate,
	string vertPath, string fragPath,
	string texColorPath, string texNormPath) : 

	Model3D(name, pathName, pos,  scale,  rotate, vertPath,  fragPath){

	//Texture here
    textureMaker.makeTex2D(&textureColor, texColorPath, TOWNHOUSE_COLOR);

	loadTownhouse();
}

void Townhouse::loadTownhouse(){
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

void Townhouse::update(){
    transformation_matrix = translate(identity_matrix, position);
    transformation_matrix = scale(transformation_matrix, scaling);
    transformation_matrix = rotate(transformation_matrix, radians(rotation.x), vec3(1, 0, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.y), vec3(0, 1, 0));
    transformation_matrix = rotate(transformation_matrix, radians(rotation.z), vec3(0, 0, 1));

    unsigned int transformLocation = glGetUniformLocation(shaderMaker.getShaderProg(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(transformation_matrix));
}

void Townhouse::assignTexture(){
    GLuint texAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "texTownhouseColor");
    textureMaker.setActiveTex(TOWNHOUSE_COLOR);
    glUniform1i(texAddress, TOWNHOUSE_COLOR);
 
    glBindTexture(GL_TEXTURE_2D, textureColor);
}

void Townhouse::draw(){
    update();
    assignTexture();
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
}