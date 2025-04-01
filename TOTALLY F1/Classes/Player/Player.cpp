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
	playerCameras[THIRD_PERSON]->updateThirdPers(playerKart[PLYR_IDX_KL]->getPosition());
	
	playerCameras[FIRST_PERSON]->updateFirstPers(
		playerKart[PLYR_IDX_KL]->getPosition(),
		playerKart[PLYR_IDX_KL]->getDirection());
}

void Player::rotateThirdPersKeys(MOVE move) {
	playerCameras[THIRD_PERSON]->rotateWithKeys(move);
}

void Player::rotateThirdPersMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	playerCameras[THIRD_PERSON]->rotateWithMouse(prevMousePos, currMousePos);
	playerCameras[THIRD_PERSON]->checkRotation();
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

void Player::reverseKart(bool reverse) {
	for (PlayerKart* kartPart : playerKart)
		kartPart->setReverse(reverse);
}