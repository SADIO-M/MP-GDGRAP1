#version 330 core

//Skybox fragment shader
//Since there are two types of skyboxes (morning or night), it just switches between the two

out vec4 FragColor;

in vec3 texCoord;

uniform samplerCube mornSkybox;
uniform samplerCube nightSkybox;

uniform int selectSkybox;
//Switches the skybox texture
void main(){
	if(selectSkybox == 0) // NIGHT
		FragColor = texture(nightSkybox, texCoord);
	else if(selectSkybox == 1) // MORNING
		FragColor = texture(mornSkybox, texCoord);
}
