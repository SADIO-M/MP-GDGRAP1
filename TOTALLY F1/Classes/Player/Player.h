#pragma once

#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

#include "PlayerKart.h"
#include "../Cameras/Perspective.h"

/*
	This is the Player class
		- Handles most of the player-related objects, cameras, and controls
		- Contains a vector of the PlayerKart (since again, the kart is split into 3 shapes)
		- Has a vector of the perspective cameras, to hold both the third person and first person cameras
		- Also contains which camera is active, so the game knows which one to draw 

	[Created by: Megan Sadio & Yza Montuerto]
*/
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
	void reverseKart(bool reverse);

	void switchCam(ACTIVE_CAM camIndex);
	void updateCameras();
	void rotateThirdPersMouse(dvec2* prevMousePos, dvec2* currMousePos);
	void rotateThirdPersKeys(MOVE move);


	//GETTERS & SETTERS
	void addPlayerKart(PlayerKart* kartPart);
	void addPlayerCamera(Perspective* camera);

	PlayerKart* getKartPart(PLYR_KART_PARTS kartIndex);
	vector<PlayerKart*> getWholeKart();

	Perspective* getActiveCam();
	vector<Perspective*> getAllCameras();
};