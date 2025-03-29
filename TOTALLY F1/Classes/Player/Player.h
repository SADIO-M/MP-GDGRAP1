#pragma once

#include "../../Config/namespace.h"

#include "../../Classes/Models/Kart.h"
#include "../../Classes/Cameras/Perspective.h"

class Player {
private:
	vector<Kart*> playerKart;

	Perspective activeCamera;
public:
	//CONSTRUCTORS
	Player();
	Player(Kart kart, Perspective camera);

	//FUNCTIONS
	void moveCamera();
	void moveKart();

	//GETTERS
	void setActiveCamera();
	Perspective getCamera();
};