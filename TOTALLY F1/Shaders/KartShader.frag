#version 330 core

//This is the fragment shader for the Kart Object

/////////// TEXTURES ///////////
uniform sampler2D texLivery;
uniform sampler2D texWheel;
uniform sampler2D texCover;
uniform int selectTex;

/////////// POINT LIGHT ///////////
uniform vec3 pointPos;
uniform vec3 pointColor;

uniform float pointAmbStr;
uniform vec3 pointAmbColor;

uniform float pointSpecStr;
uniform float pointSpecPhong;

uniform float pointBright;
uniform float quadMod;
uniform float linearMod;
uniform float constantMod;

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

//This function creates the point light from the passed uniform vectors
//This is a point light because it calculates the distance between the light and adjusts the brightness accordingly
vec4 createPointLight(){
	vec3 normal = normalize(normCoord);
	vec3 lightDir = normalize(pointPos - fragPos);
	float lightDistance = length(pointPos - fragPos);
	float adjustBrightness = 1.0f / (constantMod + 
								linearMod * lightDistance + 
								quadMod * (lightDistance * lightDistance));

	adjustBrightness *= pointBright;

	float pointDiff = max(dot(normal, lightDir), 0.0f);
	vec3 P_Diffuse = pointDiff * pointColor;

	vec3 P_Ambient = pointAmbColor * pointAmbStr;
	vec3 viewDir = normalize(cameraPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float pointSpec = pow(max(dot(reflectDir, viewDir), 0.1), pointSpecPhong);
	vec3 P_Specular = pointSpec * pointSpecStr * pointColor;

	return vec4(P_Diffuse + P_Ambient + P_Specular, 1.0f) * adjustBrightness;
}

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

	return vec4(D_Diffuse + D_Ambient + D_Specular, 1.0f) * dirBright;
}

//In the main function, the lights are added together
//Then, depending on selectTex, it assigns the corresponding texture
void main(){
	vec4 pointLight = createPointLight();
	vec4 directionLight = createDirectionLight();
	vec4 allLights = pointLight + directionLight;

	if (selectTex == 0) 
		FragColor = allLights * texture(texLivery, texCoord); 
	
	else if (selectTex == 1) 
		FragColor = allLights * texture(texWheel, texCoord); 
	
	else if (selectTex == 2) 
		FragColor = allLights * texture(texCover, texCoord); 
}