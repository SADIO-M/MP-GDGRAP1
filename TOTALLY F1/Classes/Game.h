#pragma once

#include "../Config/namespace.h"

#include "CShaders/Shader.h"

#include "Skybox/Skybox.h"

#include "Models/Model3D.h"
#include "Models/LightBall.h"
#include "Models/Kart.h"

#include "Lights/Direction.h"
#include "Lights/Point.h"

#include "Cameras/Orthographic.h"
#include "Cameras/Perspective.h"

/* This is the Game class
       - Deals with the program's main functions such as input handling and other controls
       - Contains information on models 
       - Controls the program information and main loop
 
   [Created by: Yza Montuerto]
*/
class Game {
private:
    // Window information
    GLFWwindow* window;
    float windowWidth;
    float windowHeight;

    // Vector containing all models (The kart and its shapes, and the light ball)
    vector<Model3D*> allModels;
    Skybox* skybox;

    // Model VAOs
    // The kart object has three shapes, so to load all of it it needs three VAOs
    GLuint kartVAOs[3];
    GLuint light_ballVAO;
    GLuint skyboxVAO;

    // Variable for cooldown on control object toggle
    int internalTime = 0;
       
    // bools referring to which object the player is controlling and which camera view is being used
    bool controlKart;
    bool controlPersCam;
    //Controls the skybox texture
    SELECT_TEXTURE skyboxTex = MORNING;

    // Mouse position information
    dvec2 currMousePos;
    dvec2 prevMousePos;

    ///////////////// LIGHTING /////////////////
        //Point Light
    Point pointLight = Point(
        vec3(-5, 0.5, 0),       // Light Position
        vec3(1.0f),             // Light Color
        0.5f,                   // Ambient Strength
        0.5f,                   // Specular Strength
        10.0f,                  // Specular Phong
        75.0f,                  // Brightness
        0.05f,                  // Brightness modifier (how much the brightness adjusts)
        2.0f,                   // Quadratic term
        2.0f,                   // Linear term
        2.0f                    // Constant term
    );                          // The quadratic, linear, and constant term affect the distance at which the light starts to fall off

        //Direction Light
    Direction dirLight = Direction(
        vec3(4.0f, -5.0f, 0.0f),// Light Position
        vec3(1.0f, 1.0f, 1.0f), // Light Color
        1.0f,                   // Ambient Strength
        1.0f,                   // Specular Strength
        15.0f,                  // Specular Phong
        0.5f,                   // Brightness
        0.001f,                 // Brightness modifier 
        vec3(4.0f, -5.0f, 0.0f) // Direction of the light
    );

    ///////////////// CAMERAS /////////////////
        //Orthographic Camera
    Orthographic orthoCam = Orthographic(
        800.0f,                 // Window width
        800.0f,                 // Window height
        -30.0f,                 // zNear
        30.0f,                  // zFar
        vec3(0.0, 10.0, 0.0),   // Camera Position
        vec3(0.0),              // Camera Center
        vec3(-0.5f, 0.0f, 0.0f),// Camera Rotation Modifier (how much the camera gets rotated)
        -10.0f,                 // Left most point
        10.0f,                  // Right most point
        -10.0f,                 // Top most point
        10.0f                   // Bottom most point
    );

        //Perspective Camera
    Perspective persCam = Perspective(
        800.0f,                 // Window width
        800.0f,                 // Window height
        0.1f,                   // zNear
        100.0f,                 // zFar
        vec3(0.0f, 1.0f, -8.0f),// Camera Position
        vec3(0.0f),             // Camera Center
        vec3(0.0f),             // Camera Rotation Modifier
        60.0f                   // Field of view (FOV)
    );

public:
    //CONSTRUCTORS
    Game();
    Game(GLFWwindow* window, float windowWidth, float windowHeight);

    //FUNCTIONS
    void start();
    void initializeSkybox();
    void initializeModels();
    void runLoop();

    void setVAO(GLuint* VAO, int type);
   
    void checkInput();
    void mouseInput();

    //DECONSTRUCTOR
    ~Game();
};