#include "Player.h"

Player::Player(){}

void Player::moveInput(DRIVING move) {
	for (PlayerKart* kartPart : playerKart)
		kartPart->move(move);
}

void Player::switchCam(ACTIVE_CAM camIndex) {
	activeCamera = playerCameras[camIndex];
}

void Player::updateCameras() {
	for (Perspective* camera : playerCameras){
		camera->setPosMod(playerKart[PLYR_IDX_KL]->getPosition());
		camera->update();
	}
}

void Player::rotateThirdPersKeys(MOVE move) {
	playerCameras[THIRD_PERSON]->rotateWithKeys(move);
}

void Player::rotateThirdPersMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	playerCameras[THIRD_PERSON]->rotateWithMouse(prevMousePos, currMousePos);
	playerCameras[THIRD_PERSON]->checkCameraRotation();
}

void Player::addPlayerKart(PlayerKart* kartPart) {
	playerKart.push_back(kartPart);
}

void Player::addPlayerCamera(Perspective* camera) {
	playerCameras.push_back(camera);
}

PlayerKart* Player::getKartPart(PLYR_KART_PARTS kartIndex) { return playerKart[kartIndex]; }

vector<PlayerKart*> Player::getWholeKart() { return playerKart; }

Perspective* Player::getActiveCam() { return activeCamera; }

vector<Perspective*> Player::getAllCameras() { return playerCameras; }