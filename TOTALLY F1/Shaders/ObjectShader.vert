#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 camera_view;

out vec3 normCoord;
out vec3 fragPos;

void main(){
	normCoord = mat3(transpose(inverse(transform))) * vertexNormal;
	fragPos = vec3(transform * vec4(aPos, 1.0));

	gl_Position = projection * camera_view * transform * vec4(aPos, 1.0);
}