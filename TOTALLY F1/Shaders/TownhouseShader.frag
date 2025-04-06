#version 330 core

/////////// TEXTURE ///////////
uniform sampler2D texTownhouseColor;

/////////// SIGNAL LIGHT ///////////
uniform vec3  signalPos;
uniform vec3  signalColor;
				
uniform float signalAmbStr;
uniform vec3  signalAmbColor;
			
uniform float signalSpecStr;
uniform float signalSpecPhong;
			
uniform float signalBright;
uniform float signalquadMod;
uniform float signallinearMod;
uniform float signalconstantMod;

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

//This function creates the point light from the passed uniform vectors
//This is a point light because it calculates the distance between the light and adjusts the brightness accordingly
vec3 createSignalLights(){
	vec3 normal = normalize(normCoord);
	vec3 viewDir = normalize(cameraPosition - fragPos);

	vec3 lightDir = normalize(signalPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float lightDistance = length(signalPos - fragPos);
	float adjustBrightness = 1.0f / (signalconstantMod + 
								signallinearMod * lightDistance + 
								signalquadMod * (lightDistance * lightDistance));

	adjustBrightness *= signalBright;

	float pointDiff = max(dot(normal, lightDir), 0.0f);
	vec3 P_Diffuse = pointDiff * signalColor;

	vec3 P_Ambient = signalAmbColor * signalAmbStr;

	float pointSpec = pow(max(dot(reflectDir, viewDir), 0.1), signalSpecPhong);
	vec3 P_Specular = pointSpec * signalSpecStr * signalColor;

	return (P_Diffuse + P_Ambient + P_Specular) * adjustBrightness;
}

//This is the function for creating a directional light
//It is similar to the point light except its direction is fixed to point at the center, 
//and its intensity does not decrease based on distance
vec3 createDirectionLight(){
	vec3 normal = normalize(normCoord);
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

vec3 createSpotLightL(){
	vec3 normal = normalize(normCoord);
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

vec3 createSpotLightR(){
	vec3 normal = normalize(normCoord);
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
	vec3 signalLights = createSignalLights();
	vec3 directionLight = createDirectionLight();
	vec3 spotLightL = createSpotLightL();
	vec3 spotLightR = createSpotLightR();
	vec4 allLights = vec4(signalLights + directionLight + 
					      spotLightL + spotLightR, 1.0f);

	FragColor = allLights * texture(texTownhouseColor, texCoord); 
}