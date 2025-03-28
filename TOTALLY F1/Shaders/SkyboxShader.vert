#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 projection;
uniform mat4 camera_view;

void main(){
	texCoord = aPos;

	vec4 position = projection * camera_view * vec4(aPos, 1.0);

	gl_Position = vec4(position.x, position.y, position.w, position.w);
}