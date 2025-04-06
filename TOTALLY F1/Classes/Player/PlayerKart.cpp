#include "PlayerKart.h"

//CONSTRUCTORS
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

//FUNCTIONS
/*
    Moves the kart based on the player's input
        - Allows acceleration, reversing, and steering left or right
        - For steering left or right specifically, it just rotates the kart to simulate turning
*/
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

/*
    Updates the player's direction and movement
        - The direction is based on where the player has turned
        - The update() it uses is from Kart, since its essentially the same
        - The +90 in turn is to make the Kart spawn and face the correct direction
        - After all the movement, it also sets reversing to false
        - This allows for the player to brake and reverse
*/
void PlayerKart::updatePlayer() {
    direction = vec3(
        1.0f * sin(radians(thetaTurn)),
        0.0f,
        1.0f * cos(radians(thetaTurn))
    );

    Kart::update();
    Kart::turn(90+thetaTurn);

    isReversing = false;
}
