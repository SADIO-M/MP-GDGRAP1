#pragma once

#include "../../Config/namespace.h"

#include "../../Classes/Models/Kart.h"
#include "../../Classes/Cameras/Perspective.h"

class Player : public Kart{
private:
	Perspective* playerCamera;
	
	float thetaTurn = 0.0f;
	float thetaMod = 0.01f;

	float deceleration = -acceleration * 0.85f;
public:
	//CONSTRUCTORS
	Player();
	Player(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texPath, float maxSPD, float accelMod,
		Perspective* newCam);

	//FUNCTIONS
	void moveInput(char keyPressed);
	void updatePlayer();

	//GETTERS
	void setKartCam(Perspective* camera);
};