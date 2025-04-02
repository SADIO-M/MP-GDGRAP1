#pragma once

#include "../../Config/namespace.h"

#include "../../Classes/Models/Kart.h"
#include "../../Classes/Cameras/Perspective.h"

class PlayerKart : public Kart{
private:
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