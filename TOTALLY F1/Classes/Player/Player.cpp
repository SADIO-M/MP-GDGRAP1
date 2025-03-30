#include "Player.h"

Player::Player(){}

Player::Player(string name, string pathName,
    vec3 pos, vec3 scale, vec3 rotate,
    string vertPath, string fragPath,
    string texPath, float maxSPD, float accelMod,
    Perspective* newCam) :
    Kart(name, pathName,
         pos, scale, rotate,
         vertPath, fragPath,
         texPath, maxSPD, accelMod) {

    playerCamera = newCam;
}

void Player::moveInput(char keyPressed) {
    switch (keyPressed) {
    case 'w': acceleration = accelMod;
        break;
    case 's': acceleration = -accelMod * 0.5f;
        break;
    case 'a': thetaTurn += thetaMod;
        break;
    case 'd': thetaTurn -= thetaMod;
        break;
    }
}

void Player::updatePlayer() {
    direction = vec3(
        1.0 * sin(radians(thetaTurn)),
        0,
        1.0 * cos(radians(thetaTurn))
    );

    Kart::update();
    playerCamera->setPosMod(position);

    //DEBBUGGING
    cout << "Speed: " << speed;
    cout << "        AccelMod: " << accelMod << endl;
}

void Player::setKartCam(Perspective* camera) {
    playerCamera = camera;
}