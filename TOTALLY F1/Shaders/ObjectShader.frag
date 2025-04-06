#version 330 core

//This ObjectShader.frag is a general shader for objects that are not textured
//These objects are the signal light balls

/////////// COLOR OF OBJECT ///////////
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

uniform vec3 cameraPosition;

in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

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

void main(){
	vec4 signalLight = createSignalLights();
	vec4 directionLight = createDirectionLight();
	vec4 allLights = signalLight + directionLight;

	FragColor = allLights * vec4(color.x, color.y, color.z, 1.0f);
}