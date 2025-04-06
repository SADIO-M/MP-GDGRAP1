#include "Light.h"

//CONSTRUCTORS
Light::Light(){}
Light::Light(vec3 position, vec3 color,
			 float ambStr, float specStr, float specPhong,
		     float brightness) {
	lightPosition = position;
	lightColor = color;

	ambientStrength = ambStr;
	ambientColor = lightColor;
	
	specularStrength = specStr;
	specularPhong = specPhong;

	this->brightness = brightness;
}

//FUNCTIONS
/*
    This loadLight function is responsible for passing the light's information to the corresponding shader program
        - For simplification, both point light and direction light have the same end variable names, and either 
            "signal", "dir", "spotL" or "spotR" is added to the start to differentiate all the lights from each other
*/
void Light::loadLight(GLuint shaderProg, string lightType) {
    GLuint lightPosAddress = glGetUniformLocation(shaderProg, (lightType+"Pos").c_str());
    glUniform3fv(lightPosAddress, 1, value_ptr(lightPosition));

    GLuint lightColorAddress = glGetUniformLocation(shaderProg, (lightType+"Color").c_str());
    glUniform3fv(lightColorAddress, 1, value_ptr(lightColor));

    GLuint ambientStrAddress = glGetUniformLocation(shaderProg, (lightType+"AmbStr").c_str());
    glUniform1f(ambientStrAddress, ambientStrength);

    GLuint ambientColorAddress = glGetUniformLocation(shaderProg, (lightType+"AmbColor").c_str());
    glUniform3fv(ambientColorAddress, 1, value_ptr(ambientColor));

    GLuint specStrAddress = glGetUniformLocation(shaderProg, (lightType+"SpecStr").c_str());
    glUniform1f(specStrAddress, specularStrength);

    GLuint specPhongAddress = glGetUniformLocation(shaderProg, (lightType+"SpecPhong").c_str());
    glUniform1f(specPhongAddress, specularPhong);

    GLuint brightAddress = glGetUniformLocation(shaderProg, (lightType+"Bright").c_str());
    glUniform1f(brightAddress, brightness);
}

/*
    This update light function is used to update the light, in case its needed to switch colors, intensity, etc.
*/
void Light::updateLight(vec3 newPos, vec3 newColor, 
                        float newAmbStr, 
                        float newSpecStr, float newSpecPhong, 
                        float newBrightness) {

    lightPosition = newPos;
    lightColor = newColor;
    ambientColor = lightColor;
    ambientStrength = newAmbStr;
    specularStrength = newSpecStr;
    specularPhong = newSpecPhong;
    brightness = newBrightness;

}

