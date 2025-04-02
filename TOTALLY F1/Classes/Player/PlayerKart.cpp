#include "PlayerKart.h"

PlayerKart::PlayerKart(){}

PlayerKart::PlayerKart(string name, string pathName,
    vec3 pos, vec3 scale, vec3 rotate,
    string vertPath, string fragPath,
    string texPath, float maxSPD, float accelMod,
    float transparency,
    float thetaTurn, float thetaMod) :
    Kart(name, pathName,
         pos, scale, rotate,
         vertPath, fragPath,
         texPath, maxSPD, accelMod,
         transparency) {

    this->thetaTurn = thetaTurn;
    this->thetaMod = thetaMod;

}

void PlayerKart::move(DRIVING move) {
    switch (move) {
        case ACCELERATE: acceleration = accelMod;
            break;
        case REVERSE: acceleration = -accelMod;
            break;
        case STEER_L: 
            thetaTurn += thetaMod * 0.05f;
            break;
        case STEER_R: 
            thetaTurn -= thetaMod * 0.05f;
            break;
    }
}

void PlayerKart::updatePlayer() {
    direction = vec3(
        1.0 * sin(radians(thetaTurn)),
        0,
        1.0 * cos(radians(thetaTurn))
    );

    Kart::update();
    Kart::turn(90+thetaTurn);

    cout << "POZ: " << position.z;
    cout << "     SPD: " << speed << endl;

    isReversing = false;
}
