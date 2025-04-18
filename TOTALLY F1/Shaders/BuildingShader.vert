#version 330 core

//This BuildingShader.vert is for the buildings that have normal mapping

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex;
//Same as other vertex shaders, but has a tan and biTan for normal mapping
layout(location = 3) in vec3 tan;
layout(location = 4) in vec3 biTan;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 camera_view;

out vec2 texCoord;
out vec3 normCoord;
out vec3 fragPos;

out mat3 TBN;

void main(){
	texCoord = aTex;
	mat3 modelMatrix = mat3(transpose(inverse(transform)));
	normCoord = modelMatrix * vertexNormal;
	fragPos = vec3(transform * vec4(aPos, 1.0));

	vec3 T = normalize(modelMatrix * tan);
	vec3 B = normalize(modelMatrix * biTan);
	vec3 N = normalize(normCoord);

	TBN = mat3(T, B, N);

	gl_Position = projection * camera_view * transform * vec4(aPos, 1.0);
}