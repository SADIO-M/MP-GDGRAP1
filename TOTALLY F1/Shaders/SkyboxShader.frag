#version 330 core

out vec4 FragColor;

in vec3 texCoord;

uniform samplerCube mornSkybox;
uniform samplerCube nightSkybox;

uniform int selectSkybox;

void main(){
	if(selectSkybox == 0) // NIGHT
		FragColor = texture(nightSkybox, texCoord);
	else if(selectSkybox == 1) // MORNING
		FragColor = texture(mornSkybox, texCoord);
}
