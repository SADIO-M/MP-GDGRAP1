#version 330 core

//This is the fragment shader for the Kart Object

/////////// TEXTURES ///////////
uniform sampler2D texLivery;
uniform sampler2D texWheel;
uniform sampler2D texCover;
uniform int selectTex;

/////////// DIRECTIONAL LIGHT ///////////
uniform vec3 dirPos;
uniform vec3 dirColor;
uniform vec3 direction;

uniform float dirAmbStr;
uniform vec3 dirAmbColor;

uniform float dirSpecStr;
uniform float dirSpecPhong;

uniform float dirBright;

uniform vec3 cameraPosition;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

//This is the function for creating a directional light
//It is similar to the point light except its direction is fixed to point at the center, 
//and its intensity does not decrease based on distance
vec4 createDirectionLight(){
	vec3 normal = normalize(normCoord);
	vec3 lightDir = normalize(direction);

	float dirDiff = max(dot(normal, lightDir), 0.0f);
	vec3 D_Diffuse = dirDiff * dirColor;

	vec3 D_Ambient = dirAmbColor * dirAmbStr;
	vec3 viewDir = normalize(cameraPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float dirSpec = pow(max(dot(reflectDir, viewDir), 0.1), dirSpecPhong);
	vec3 D_Specular = dirSpec * dirSpecStr * dirColor;

	return vec4(D_Diffuse + D_Ambient + D_Specular, 0.3f) * dirBright;
}

void main(){
	vec4 directionLight = createDirectionLight();

	if (selectTex == 2) 
		FragColor = directionLight * texture(texLivery, texCoord); 
	
	else if (selectTex == 3) 
		FragColor = directionLight * texture(texWheel, texCoord); 
	
	else if (selectTex == 4) 
		FragColor = directionLight * texture(texCover, texCoord); 
}