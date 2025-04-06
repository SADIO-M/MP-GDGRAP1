#include "Skybox.h"

//CONSTRUCTORS
Skybox::Skybox(){}
Skybox::Skybox(string* nightFaces, string* morningFaces,
	string vertPath, string fragPath) {
	
    //Sets up a VBO and EBO
    setUpVBO();
    setUpEBO();

    shaderMaker.createShader(vertPath, fragPath);

    //Calls a different texture function, since the texture of the skybox is a cube map
    textureMaker.makeTexCubeMap(&morningTex, morningFaces, MORNING);
    textureMaker.makeTexCubeMap(&nightTex, nightFaces, NIGHT);
}

//FUNCTIONS
/*
    Similar to the VBO setters before, but specifically for the skybox cube
*/
void Skybox::setUpVBO() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        &vertices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GLfloat),
        (void*)0
    );
}

/*
    Sets up the EBO for the skybox cube
*/
void Skybox::setUpEBO() {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLint) * 36,
        &indices,
        GL_STATIC_DRAW
    );

    //Enables layout 0
    glEnableVertexAttribArray(0);

    //Ensures clean up
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
    Draws the skybox cube and binds the texture based on the corresponding "time" (if it is morning or night)
*/
void Skybox::draw(mat4 viewMatrix, mat4 projMatrix, SELECT_TEXTURE texIndex){
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glUseProgram(shaderMaker.getShaderProg());
    
    //Skybox view
    skyView = mat4(1.f);
    skyView = mat4(mat3(viewMatrix));

    GLuint viewCamAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "camera_view");
    glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(skyView));

    GLuint projectionAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "projection");
    glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projMatrix));

    GLuint selectSkyboxAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "selectSkybox");

    //Sets the active texture
    textureMaker.setActiveTex(texIndex);

    //Assigns texture based on the passed tex index (if its morning or not)
    if (texIndex == MORNING) {
        GLuint skyboxAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "mornSkybox");
        glUniform1i(skyboxAddress, MORNING);
        glUniform1i(selectSkyboxAddress, MORNING);
        glBindTexture(GL_TEXTURE_CUBE_MAP, morningTex);
    }
    else if (texIndex == NIGHT) {
        GLuint skyboxAddress = glGetUniformLocation(shaderMaker.getShaderProg(), "nightSkybox");
        glUniform1i(skyboxAddress, NIGHT);
        glUniform1i(selectSkyboxAddress, NIGHT);
        glBindTexture(GL_TEXTURE_CUBE_MAP, nightTex);
    }

    //Draws the skybox
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}