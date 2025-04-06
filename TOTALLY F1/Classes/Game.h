#pragma once

#include "../Config/namespace.h"
#include "../Config/enumerations.h"

#include "Player/Player.h"
#include "Player/PlayerKart.h"

#include "Skybox/Skybox.h"

#include "Models/Model3D.h"
#include "Models/Object.h"
#include "Models/Kart.h"
#include "Models/Building.h"

#include "Lights/Direction.h"
#include "Lights/Point.h"
#include "Lights/Spot.h"

#include "Cameras/Perspective.h"

/* This is the Game class
       - Deals with the program's main functions such as input handling and other controls
       - Contains information on models, lights, and cameras
       - Controls the program information and main game loop
       - Also keeps track of when the game has ended (a.k.a when all three karts have reached the end)
       - Handles the timers for the Karts
       - Handles the skybox
 
   [Created by: Megan Sadio & Yza Montuerto]
*/
class Game {
private:
    // Window information
    GLFWwindow* window;
    float windowWidth;
    float windowHeight;

    //Player
    Player player;

    // NP stands for non-player
    // Vector of all the non-player models
    vector<Model3D*> allNPModels;
    
    //There is only one skybox, the texture simply gets switched if its morning or night
    Skybox* skybox;

    // All VAOs
    GLuint skyboxVAO;
    // The kart object has three shapes, so to load all of it it needs three VAOs
    GLuint kartVAOs[3];
    GLuint roadVAO;
    GLuint lightBallVAO;
    GLuint townhouseVAO;
    GLuint stonehouseVAO;

    //bools
    bool isThirdPerson;
    bool stopCars;
    bool gameStart;
    bool isPrinted;

    //Timer for Karts
    double startTimer;
    double elapsedTime;
    double kartFastTime = 0, playerKartTime = 0, kartSlowTime = 0;

    // Variable for cooldown on control object toggle (to prevent input spam)
    int switchCamTimer = 0;
    int stopCarsTimer = 0;
    int signalLights = 0;
       
    //Controls the skybox texture
    SELECT_TEXTURE skyboxTex = MORNING;

    // Mouse position information
    dvec2 currMousePos;
    dvec2 prevMousePos;

    ///////////////// LIGHTING /////////////////
        //Point Light (for the signal light)
    Point signalLight = Point(
        vec3(0.0f, 3.5f, 3.0f), // Light Position
        vec3(0.0f),             // Light Color
        0.0f,                   // Ambient Strength
        0.0f,                   // Specular Strength
        0.0f,                   // Specular Phong
        0.0f,                   // Brightness
        2.0f,                   // Quadratic term
        2.0f,                   // Linear term
        2.0f                    // Constant term
    );                          // The quadratic, linear, and constant term affect the distance at which the light starts to fall off

        //Direction Light (for the morning / night feel)
    Direction dirLight = Direction(
        vec3(5.0f, 15.0f, 20.0f),// Light Position
        vec3(0.9f, 1.0f, 0.9f),  // Light Color
        1.0f,                    // Ambient Strength
        5.0f,                    // Specular Strength
        15.0f,                   // Specular Phong
        1.0f,                    // Brightness
        vec3(5.0f, 15.0f, 20.0f) // Direction of the light
    );

        //Spot light for the left headlight of the player
    Spot spotLightL = Spot(
        vec3(1.0f, 1.0f, 3.0f), // Light Position
        vec3(0.0f),             // Light Color
        0.5f,                   // Ambient Strength
        0.8f,                   // Specular Strength
        15.0f,                  // Specular Phong
        50.0f,                  // Brightness
        2.0f,                   // Quadratic term
        2.0f,                   // Linear term
        2.0f,                   // Constant term
        0.90f,                  // Outer Cone
        0.95f,                  // Inner Cone
        vec3(0.0f, 0.1f, 1.0f)  // Spotlight direction
    );

        //Spot light for the right headlight of the player
    Spot spotLightR = Spot(
        vec3(-1.0f, 1.0f, 3.0f),// Light Position
        vec3(0.0f),             // Light Color
        0.5f,                   // Ambient Strength
        0.8f,                   // Specular Strength
        15.0f,                  // Specular Phong
        50.0f,                  // Brightness
        2.0f,                   // Quadratic term
        2.0f,                   // Linear term
        2.0f,                   // Constant term
        0.90f,                  // Outer Cone
        0.95f,                  // Inner Cone
        vec3(0.0f, 0.1f, 1.0f)  // Spotlight direction
    );

public:
    //CONSTRUCTORS
    Game();
    Game(GLFWwindow* window, float windowWidth, float windowHeight);

    //FUNCTIONS
    void start();
    void initializePlayer();
    void initializeSkybox();
    void initializeModels();
    void runLoop();

    void setVAO(GLuint* VAO, int type);
   
    void checkInput();
    void mouseInput();

    void updateTimers();
    void updateSignalLights();
    void checkKarts();

    //DECONSTRUCTOR
    ~Game();
};