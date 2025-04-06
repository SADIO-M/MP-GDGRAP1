#pragma once

#include "../../Config/namespace.h"

#include "../../Classes/Models/Kart.h"
#include "../../Classes/Cameras/Perspective.h"

/*
	This is the PlayerKart class
		- Handles all of the kart movement for the player kart
		- Different from the Kart class since it has more freedom of movement (steering, reversing, etc.)
		- Child of the Kart class

	[Created by: Megan Sadio]
*/
class PlayerKart : public Kart{
private:
	//For steering
	float thetaTurn;
	float thetaMod;
public:
	//CONSTRUCTORS
	PlayerKart();
	PlayerKart(string name, string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		string texPath, float maxSPD, float accelMod,
		float transparency,
		float thetaTurn, float thetaMod);

	//FUNCTIONS
	void move(DRIVING move);
	void updatePlayer();
};