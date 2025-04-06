#include "Perspective.h"

//CONSTRUCTORS
Perspective::Perspective(){}
Perspective::Perspective(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 rotation, float FOV,
	float rotSpeed, float radius) : 
	Camera(width, height, near, far, position, center, rotation) {
	
	fieldOfView = FOV;
	rotateSpeed = rotSpeed;
	cameraRadius = radius;
}

//FUNCTIONS
/*
	This rotate with mouse function is the same as previously used ones 
		- It gets the previous position and current position of the mouse, 
		  and updates the camera rotation matrix
*/
void Perspective::rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	cameraRotation.x += (prevMousePos->x - currMousePos->x) * rotateSpeed;
	cameraRotation.y += (currMousePos->y - prevMousePos->y) * rotateSpeed;
	prevMousePos->x = currMousePos->x;
	prevMousePos->y = currMousePos->y;
}
/*
	This allows for rotation with the arrow keys
		- Added the * 5 so it was a little faster
*/
void Perspective::rotateWithKeys(MOVE move) {
	switch (move) {
	case UP:    cameraRotation.y -= rotateSpeed * 5;
		break;				   
	case DOWN:  cameraRotation.y += rotateSpeed * 5;
		break; 
	case LEFT:  cameraRotation.x += rotateSpeed * 5;
		break;
	case RIGHT: cameraRotation.x -= rotateSpeed * 5;
		break;
	}
}

/*
	This fixes the rotation so that the third person camera doesnt go below the road plane
		(Ok for some reason, the camera's axis got switched, and we're too scared to mess with it so
		 ignore the fact its the y axis :D )
*/
void Perspective::checkRotation() {
	if (cameraRotation.y >  -2.0f) cameraRotation.y =  -2.0f;
	if (cameraRotation.y < -70.0f) cameraRotation.y = -70.0f;
}

/*
	This updates the third person camera (since it rotates around the player)
		- Since the player is essentially the pivot point, it calculates its X, Y, and Z position based on the
		  player's kart position
		- After that it updates its position and its camera center
*/
void Perspective::updateThirdPers(vec3 position){
	float rotXRadians = radians(cameraRotation.x);
	float rotYRadians = radians(cameraRotation.y);
	float fromGround  = cos(rotYRadians) * cameraRadius;

	float newPosX = fromGround    * sin(rotXRadians) + cameraCenter.x;
	float newPosY = -cameraRadius * sin(rotYRadians) + cameraCenter.y;
	float newPosZ = fromGround    * cos(rotXRadians) + cameraCenter.z;

	cameraPosition = vec3(newPosX, newPosY, newPosZ);
	cameraCenter = position;
}

/*
	This updates the first person camera, and since it doesn't move it just updates its position based on
	the player's kart position
		- However, since it faces according to where the player turns, its camera center considers the direction of the player
*/
void Perspective::updateFirstPers(vec3 position, vec3 direction) {
	cameraPosition = position + vec3(0.0f, 1.5f, 0.5f);
	cameraCenter = cameraPosition + direction;
}

/*
	Draws the camera.
		- It also passes the camera to the object's corresponding shader program
*/
void Perspective::draw(GLuint shaderProg){
	viewMatrix = lookAt(cameraPosition, cameraCenter, worldUp);

	// Perspective projection matrix
	projectionMatrix = perspective(
		radians(fieldOfView),
		windowHeight / windowWidth,
		zNear,
		zFar);

	// Passes values to shader program
	GLuint cameraPositionAddress = glGetUniformLocation(shaderProg, "cameraPosition");
	glUniform3fv(cameraPositionAddress, 1, value_ptr(cameraPosition));

	GLuint viewCamAddress = glGetUniformLocation(shaderProg, "camera_view");
	glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(viewMatrix));

	GLuint projectionAddress = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projectionMatrix));
}
