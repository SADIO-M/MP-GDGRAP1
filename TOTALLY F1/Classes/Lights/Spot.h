#pragma once

#include "Point.h"
#include "../../Config/namespace.h"
#include "../../Config/enumerations.h"

class Spot : public Point {
private:
	float outerCone;
	float innerCone;
	vec3 spotDir;
	float turnSpeed = 0.0375f;
public:
	Spot();
	Spot(vec3 position, vec3 color,
		float ambStr, float specStr, float specPhong,
		float brightness,
		float quadratic, float linear, float constant,
		float outer, float inner, vec3 dir);

	void loadSpot(GLuint shaderProg, string lightType);
	void updateSpotPosDir(vec3 kartPos, vec3 kartDir);
	void spotSpin(MOVE move);
};