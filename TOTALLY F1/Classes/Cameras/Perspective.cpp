#include "Perspective.h"

//CONSTRUCTORS
Perspective::Perspective(){}

Perspective::Perspective(float width, float height,
						float near, float far,
						vec3 position, vec3 center,
						vec3 positionMod, vec3 rotationMod,
						float fov) :

	Camera(width, height, near, far, position, center, positionMod, rotationMod) {

	initialPosition = camPosition;
	fieldOfView = fov;
}

//FUNCTIONS
/*
	This rotateWithMouse handles the rotation using the mouse and calculates the rotation
		- Updates the camRotationMod, the modifier responsible for the camera's rotation
		- Gets the rotation from the previous mouse position and updates the current x and y accordingly
		- Rotate speed is for camera rotation sensitivity
*/
void Perspective::rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	camRotationMod.x += (currMousePos->y - prevMousePos->y) * rotateSpeed;
	camRotationMod.y += (prevMousePos->x - currMousePos->x) * rotateSpeed;

	prevMousePos->x = currMousePos->x;
	prevMousePos->y = currMousePos->y;
}

/*
	This function allows camera rotation with the keys (I, J, K, L)
*/
void Perspective::rotateWithKeys(MOVE move) {
	switch (move) {
		case UP: camRotationMod.x -= rotateSpeed * 5;
			break;									
		case DOWN: camRotationMod.x += rotateSpeed * 5;
			break;									
		case LEFT: camRotationMod.y += rotateSpeed * 5;
			break;									
		case RIGHT: camRotationMod.y -= rotateSpeed * 5;
			break;
	}
}

/*
	This function checks the camera's rotation on the x-axis 
		- This is because when the x rotation goes over a certain threshold, the camera flips
		- This is to avoid that camera flipping for a cleaner experience
*/
void Perspective::checkCameraRotation() {
	//Limits the rotation of the mouse, can be edited to allow more range of mouse movement
	if (camRotationMod.x > 45.0f) camRotationMod.x = 45.0f;
	if (camRotationMod.x < -45.0f) camRotationMod.x = -45.0f;
	//if (camRotationMod.y > 45.0f) camRotationMod.y = 45.0f;
	//if (camRotationMod.y < -45.0f) camRotationMod.y = -45.0f;
}

/*
	This function draws the perspective camera, it is similar to the Orthographic's draw function, 
		except the projectionMatrix = perspective()
*/
void Perspective::draw(GLuint shaderProg) {
	// View matrix to always look at the center
	viewMatrix = lookAt(camPosition, camCenter, worldUp);

	// Projection matrix is perspective
	projectionMatrix = perspective(
		radians(fieldOfView),
		windowHeight / windowWidth,
		zNear,
		zFar);

	// Passes values to shader program
	GLuint cameraPositionAddress = glGetUniformLocation(shaderProg, "cameraPosition");
	glUniform3fv(cameraPositionAddress, 1, value_ptr(camPosition));

	GLuint viewCamAddress = glGetUniformLocation(shaderProg, "camera_view");
	glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(viewMatrix));

	GLuint projectionAddress = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projectionMatrix));
}
