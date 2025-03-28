#version 330 core

//This is the fragment shader for the Light Ball Object

//This is the color that gets applied to the light ball
uniform vec3 color;

out vec4 FragColor;

void main(){
	FragColor = vec4(color.x, color.y, color.z, 1.0f);
}