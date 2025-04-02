#version 330 core

//This is the fragment shader for the Kart Object

/////////// TEXTURES ///////////
uniform sampler2D texLivery;
uniform sampler2D texWheel;
uniform sampler2D texCover;
uniform int selectTex;

/////////// LIGHTS ON ///////////
uniform int lightsOn;

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

/////////// SPOT HEADLIGHT ///////////
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

/////////// OTHER VARIABLES ///////////
uniform vec3 cameraPosition;
uniform float transparency; 

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

//This function creates the point light from the passed uniform vectors
//This is a point light because it calculates the distance between the light and adjusts the brightness accordingly
vec4 createSignalLights(){
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

	return vec4(P_Diffuse + P_Ambient + P_Specular, transparency) * adjustBrightness;
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

	return vec4(D_Diffuse + D_Ambient + D_Specular, transparency) * dirBright;
}

vec4 createSpotLightL(){
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
		return vec4(SP_Diffuse * inten + SP_Ambient + SP_Specular * inten, transparency) * adjustBrightness;
	else 
		return vec4(SP_Ambient, transparency) * adjustBrightness;
}

//In the main function, the lights are added together
//Then, depending on selectTex, it assigns the corresponding texture
void main(){
	vec4 signalLights = createSignalLights();
	vec4 directionLight = createDirectionLight();
	vec4 spotLightL = createSpotLightL();
	vec4 allLights = signalLights + 
				     directionLight + 
					 spotLightL;

	if (selectTex == 2) 
		FragColor = allLights * texture(texLivery, texCoord); 
	
	else if (selectTex == 3) 
		FragColor = allLights * texture(texWheel, texCoord); 
	
	else if (selectTex == 4) 
		FragColor = allLights * texture(texCover, texCoord); 
}