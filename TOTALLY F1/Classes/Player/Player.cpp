#include "Player.h"

//CONSTRUCTOR
Player::Player(){}

//FUNCTIONS
/*
	This moves the kart based on the input
*/
void Player::moveInput(DRIVING move) {
	for (PlayerKart* kartPart : playerKart)
		kartPart->move(move);
}

/*
	This sets the kart if its reversing or not (for movement related purposes)
*/
void Player::reverseKart(bool reverse) {
	for (PlayerKart* kartPart : playerKart)
		kartPart->setReverse(reverse);
}

/*
	This switches the active camera
*/
void Player::switchCam(ACTIVE_CAM camIndex) {
	activeCamera = playerCameras[camIndex];
}

/*
	This updates all of the camera's positions and directions, especially when the player moves
		- Even if the camera isn't the active one, it still gets updated regardless
*/
void Player::updateCameras() {
	playerCameras[THIRD_PERSON]->updateThirdPers(playerKart[PLYR_IDX_KL]->getPosition());
	
	playerCameras[FIRST_PERSON]->updateFirstPers(
		playerKart[PLYR_IDX_KL]->getPosition(),
		playerKart[PLYR_IDX_KL]->getDirection());
}

/*
	Rotates the third person camera with the mouse (since the first person camera can't do that)
*/
void Player::rotateThirdPersMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	playerCameras[THIRD_PERSON]->rotateWithMouse(prevMousePos, currMousePos);
	playerCameras[THIRD_PERSON]->checkRotation();
}

/*
	Similar to the third person mouse rotation, except with keys only
*/
void Player::rotateThirdPersKeys(MOVE move) {
	playerCameras[THIRD_PERSON]->rotateWithKeys(move);
}

//GETTERS & SETTERS
/*
	Adds a part of the kart to the player kart vector
*/
void Player::addPlayerKart(PlayerKart* kartPart) {
	playerKart.push_back(kartPart);
}
/*
	Adds a camera to the camera vector
*/
void Player::addPlayerCamera(Perspective* camera) {
	playerCameras.push_back(camera);
}
//Returns a specific kart part
PlayerKart* Player::getKartPart(PLYR_KART_PARTS kartIndex) { return playerKart[kartIndex]; }
//Returns the whole kart
vector<PlayerKart*> Player::getWholeKart() { return playerKart; }
//Gets the active camera
Perspective* Player::getActiveCam() { return activeCamera; }
//Gets all the cameras
vector<Perspective*> Player::getAllCameras() { return playerCameras; }