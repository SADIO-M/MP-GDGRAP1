#version 330 core

uniform vec3 color;

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
uniform vec3  spotPos;
uniform vec3  spotColor;
				
uniform float spotAmbStr;
uniform vec3  spotAmbColor;
			  
uniform float spotSpecStr;
uniform float spotSpecPhong;
			  
uniform float spotBright;
uniform float spotquadMod;
uniform float spotlinearMod;
uniform float spotconstantMod;
uniform float spotOuterCone;
uniform float spotInnerCone;
uniform vec3  spotDir;

/////////// OTHER VARIABLES ///////////
uniform vec3 cameraPosition;

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

vec4 createSpotLight1(){
	vec3 normal = normalize(normCoord);
	vec3 viewDir = normalize(cameraPosition - fragPos);

	vec3 lightDir = normalize(spotPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float lightDistance = length(spotPos - fragPos);
	float adjustBrightness = 1.0f / (spotconstantMod + 
								spotlinearMod * lightDistance + 
								spotquadMod * (lightDistance * lightDistance));

	adjustBrightness *= spotBright;

	float spotDiff = max(dot(normal, lightDir), 0.0f);
	vec3 SP_Diffuse = spotDiff * spotColor;

	vec3 SP_Ambient = spotAmbColor * spotAmbStr;

	float spotSpec = pow(max(dot(reflectDir, viewDir), 0.1), spotSpecPhong);
	vec3 SP_Specular = spotSpec * spotSpecStr * spotColor;

	float angle = dot(spotDir, -lightDir);
	float inten = clamp((angle - spotOuterCone) / (spotInnerCone - spotOuterCone), 0.0f, 1.0f);

	if(angle > spotOuterCone)
		return vec4(SP_Diffuse * inten + SP_Ambient + SP_Specular * inten, 1.0f) * adjustBrightness;
	else 
		return vec4(SP_Ambient, 1.0f) * adjustBrightness;
}

void main(){
	vec4 signalLights = createSignalLights();
	vec4 directionLight = createDirectionLight();
	vec4 spotLight1 = createSpotLight1();
	vec4 allLights = signalLights + 
				     directionLight + 
					 spotLight1;

	FragColor = allLights * vec4(color.x, color.y, color.z, 1.0f); 
}