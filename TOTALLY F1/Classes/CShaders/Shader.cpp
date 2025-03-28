#include "Shader.h"

//CONSTRUCTOR
Shader::Shader(){}

//FUNCTION
/*
   Takes care of the construction of specific shaders.
       - Recieves the path names for the vertex and fragment files to be used.
       - Attaches the shaders to the shaderProg and links shaderProg
*/
void Shader::createShader(string vertPath, string fragPath) {
    GLuint vertexShader;
    GLuint fragmentShader;

    shaderProg = glCreateProgram();

    // Setting up the vertex shader
    fstream vertexSrc(vertPath);
    stringstream vertexBuffer;
    vertexBuffer << vertexSrc.rdbuf();
    string vertexString = vertexBuffer.str();
    const char* vert = vertexString.c_str();

    // Setting up the fragment shader
    fstream fragmentSrc(fragPath);
    stringstream fragmentBuffer;
    fragmentBuffer << fragmentSrc.rdbuf();
    string fragmentString = fragmentBuffer.str();
    const char* frag = fragmentString.c_str();

    // Creation of the vertex shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vert, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag, NULL);
    glCompileShader(fragmentShader);

    // Attaching shaders and program linking
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragmentShader);
    glLinkProgram(shaderProg);

    //Clean-up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//GETTER
GLuint Shader::getShaderProg() {
    return shaderProg;
}