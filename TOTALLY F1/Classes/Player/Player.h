#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "PlayerKart.h"
#include "../Cameras/Perspective.h"


class Player {
private:
	vector<PlayerKart*> playerKart;
	vector<Perspective*> playerCameras;

	Perspective* activeCamera;
public:
	//CONSTRUCTOR
	Player();
	
	//FUNCTIONS
	void moveInput(DRIVING move);
	void switchCam(ACTIVE_CAM camIndex);
	void updateCameras();
	void rotateThirdPersKeys(MOVE move);
	void rotateThirdPersMouse(dvec2* prevMousePos, dvec2* currMousePos);

	//GETTERS
	void addPlayerKart(PlayerKart* kartPart);
	void addPlayerCamera(Perspective* camera);

	PlayerKart* getKartPart(PLYR_KART_PARTS kartIndex);
	vector<PlayerKart*> getWholeKart();

	Perspective* getActiveCam();
	vector<Perspective*> getAllCameras();
};