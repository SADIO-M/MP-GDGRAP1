#version 330 core

/////////// TEXTURES ///////////
uniform sampler2D texTownhouseColor;
uniform sampler2D texTownhouseNormal;

/////////// DIRECTIONAL LIGHT ///////////
uniform vec3 dirPos;
uniform vec3 dirColor;
uniform vec3 direction;

uniform float dirAmbStr;
uniform vec3 dirAmbColor;

uniform float dirSpecStr;
uniform float dirSpecPhong;

uniform float dirBright;

/////////// SPOT HEADLIGHT LEFT ///////////
uniform vec3  spotLPos;
uniform vec3  spotLColor;
				
uniform float spotLAmbStr;
uniform vec3  spotLAmbColor;
			  
uniform float spotLSpecStr;
uniform float spotLSpecPhong;
			  
uniform float spotLBright;
uniform float spotLquadMod;
uniform float spotLlinearMod;
uniform float spotLconstantMod;
uniform float spotLOuterCone;
uniform float spotLInnerCone;
uniform vec3  spotLDir;

/////////// SPOT HEADLIGHT RIGHT ///////////
uniform vec3  spotRPos;
uniform vec3  spotRColor;
				  
uniform float spotRAmbStr;
uniform vec3  spotRAmbColor;
			  	  
uniform float spotRSpecStr;
uniform float spotRSpecPhong;
			  	  
uniform float spotRBright;
uniform float spotRquadMod;
uniform float spotRlinearMod;
uniform float spotRconstantMod;
uniform float spotROuterCone;
uniform float spotRInnerCone;
uniform vec3  spotRDir;

/////////// OTHER VARIABLES ///////////
uniform vec3 cameraPosition;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

in mat3 TBN;

//This is the function for creating a directional light
//It is similar to the point light except its direction is fixed to point at the center, 
//and its intensity does not decrease based on distance
vec3 createDirectionLight(vec3 normal){
	vec3 lightDir = normalize(direction);

	float dirDiff = max(dot(normal, lightDir), 0.0f);
	vec3 D_Diffuse = dirDiff * dirColor;

	vec3 D_Ambient = dirAmbColor * dirAmbStr;
	vec3 viewDir = normalize(cameraPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float dirSpec = pow(max(dot(reflectDir, viewDir), 0.1), dirSpecPhong);
	vec3 D_Specular = dirSpec * dirSpecStr * dirColor;

	return (D_Diffuse + D_Ambient + D_Specular) * dirBright;
}

vec3 createSpotLightL(vec3 normal){
	vec3 viewDir = normalize(cameraPosition - fragPos);

	vec3 lightDir = normalize(spotLPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float lightDistance = length(spotLPos - fragPos);
	float adjustBrightness = 1.0f / (spotLconstantMod + 
								spotLlinearMod * lightDistance + 
								spotLquadMod * (lightDistance * lightDistance));

	adjustBrightness *= spotLBright;

	float spotLDiff = max(dot(normal, lightDir), 0.0f);
	vec3 SP_Diffuse = spotLDiff * spotLColor;

	vec3 SP_Ambient = spotLAmbColor * spotLAmbStr;

	float spotLSpec = pow(max(dot(reflectDir, viewDir), 0.1), spotLSpecPhong);
	vec3 SP_Specular = spotLSpec * spotLSpecStr * spotLColor;

	float angle = dot(spotLDir, -lightDir);
	float inten = clamp((angle - spotLOuterCone) / (spotLInnerCone - spotLOuterCone), 0.0f, 1.0f);

	if(angle > spotLOuterCone)
		return (SP_Diffuse * inten + SP_Ambient + SP_Specular * inten) * adjustBrightness;
	else 
		return (SP_Ambient) * adjustBrightness;
}

vec3 createSpotLightR(vec3 normal){
	vec3 viewDir = normalize(cameraPosition - fragPos);

	vec3 lightDir = normalize(spotRPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float lightDistance = length(spotRPos - fragPos);
	float adjustBrightness = 1.0f / (spotRconstantMod + 
								spotRlinearMod * lightDistance + 
								spotRquadMod * (lightDistance * lightDistance));

	adjustBrightness *= spotRBright;

	float spotRDiff = max(dot(normal, lightDir), 0.0f);
	vec3 SP_Diffuse = spotRDiff * spotRColor;

	vec3 SP_Ambient = spotRAmbColor * spotRAmbStr;

	float spotRSpec = pow(max(dot(reflectDir, viewDir), 0.1), spotRSpecPhong);
	vec3 SP_Specular = spotRSpec * spotRSpecStr * spotRColor;

	float angle = dot(spotRDir, -lightDir);
	float inten = clamp((angle - spotROuterCone) / (spotRInnerCone - spotROuterCone), 0.0f, 1.0f);

	if(angle > spotROuterCone)
		return (SP_Diffuse * inten + SP_Ambient + SP_Specular * inten) * adjustBrightness;
	else 
		return (SP_Ambient) * adjustBrightness;
}

//In the main function, the lights are added together
//Then, depending on selectTex, it assigns the corresponding texture
void main(){
	vec3 normal = texture(texTownhouseNormal, texCoord).rgb;
	normal = normalize(normal * 5.0f - 1.0f);
	normal = normalize(TBN * normal);

	vec3 directionLight = createDirectionLight(normal);
	vec3 spotLightL = createSpotLightL(normal);
	vec3 spotLightR = createSpotLightR(normal);
	vec4 allLights = vec4(directionLight + 
					      spotLightL + spotLightR, 1.0f);

	FragColor = allLights * texture(texTownhouseColor, texCoord); 
}