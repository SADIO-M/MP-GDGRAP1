#include "PlayerKart.h"

PlayerKart::PlayerKart(){}

PlayerKart::PlayerKart(string name, string pathName,
    vec3 pos, vec3 scale, vec3 rotate,
    string vertPath, string fragPath,
    string texPath, float maxSPD, float accelMod,
    float thetaTurn, float thetaMod) :
    Kart(name, pathName,
         pos, scale, rotate,
         vertPath, fragPath,
         texPath, maxSPD, accelMod) {

    this->thetaTurn = thetaTurn;
    this->thetaMod = thetaMod;

}

void PlayerKart::move(DRIVING move) {
    switch (move) {
        case ACCELERATE: acceleration = accelMod;
            break;
        case REVERSE: acceleration = -accelMod * 0.5f;
            break;
        case STEER_L: thetaTurn += thetaMod;
            break;
        case STEER_R: thetaTurn -= thetaMod;
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

    //DEBBUGGING
    //if (position.z >= 10000) cout << "WIN!!" << endl;
    //else cout << "POS Z: " << position.z << endl;

    //cout << "Speed: " << speed;
    //cout << "        Accel: " << acceleration << endl;
}