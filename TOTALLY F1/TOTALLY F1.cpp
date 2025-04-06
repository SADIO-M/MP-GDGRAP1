/*
    ////////// MACHINE PROJECT : GDGRAP1 - S22 //////////

    Submitted by:
        SADIO, Megan Florence Sophia C.
        MONTUERTO, Yzabelle Anne A.
    Submitted on: April 7, 2025

    ////////// MODEL CREDITS //////////
        *For the models that have textures, they also come from the same link
        
        F1 2026 Car:
        Nimaxo3D. (2024). F1 2026 Release Car Free 3D model. [3D digital model].
            https://www.cgtrader.com/free-3d-models/car/racing-car/f1-2026-release-car

        Light Ball:
        xuzi. (2022). ball1 sphere Free low-poly 3D model. [3D digital model].
            https://www.cgtrader.com/free-3d-models/industrial/other/ball1

        Plane:
        Plane Model was used from class.

    ////////// SKYBOX CREDITS //////////
        Morning Skybox:
        JasperCarmack. (2021, September 6). 
            Winters mourn 03 skybox textures - a mod for Source Engine [Digital Art]. 
            Gamebanana. https://gamebanana.com/mods/320017

        Night Skybox:
        JasperCarmack. (2021, August 28). 
            Night sky 02 skybox textures - a mod for Source Engine [Digital Art]. 
            Gamebanana. https://gamebanana.com/mods/317757

    ////////// NOTES //////////
        Cursor is disabled, press [Esc] to exit
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

////////// EXTERNAL LIBRARIES //////////
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef TINYOBJ_H
    #define TINYOBJ_H
    #define TINYOBJLOADER_IMPLEMENTATION
    #include "tiny_obj_loader.h"
#endif

#ifndef STB_H
    #define STB_H
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

////////// CLASSES //////////
/* GAME CLASS */
#include "Classes/Game.h"
/* SHADER AND TEXTURE CLASSES */
#include "Classes/CShaders/Shader.h"
#include "Classes/TextureMaker/TextureMaker.h"
/* SKYBOX */
#include "Classes/Skybox/Skybox.h"
/* PLAYER-RELATED CLASSES */
#include "Classes/Player/Player.h"
#include "Classes/Player/PlayerKart.h"
/* MODEL-RELATED CLASSES */
#include "Classes/Models/Model3D.h"
#include "Classes/Models/Object.h"
#include "Classes/Models/Kart.h"
#include "Classes/Models/Building.h"
/* CAMERA CLASSES */
#include "Classes/Cameras/Camera.h"
#include "Classes/Cameras/Perspective.h"
/* LIGHT CLASSES */
#include "Classes/Lights/Light.h"
#include "Classes/Lights/Direction.h"
#include "Classes/Lights/Point.h"

////////// CONFIGURATIONS //////////
#include "Config/namespace.h"
#include "Config/enumerations.h"



int main(void)
{
    GLFWwindow* window;
    //Set the window width and height
    float windowWidth  = 800.0f,
          windowHeight = 800.0f;

    if (!glfwInit()) return -1;
        window = glfwCreateWindow(windowWidth, windowHeight, "TOTALLY F1! | GDGRAP1 MP - SADIO & MONTUERTO | Press [Esc] to Exit", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //This set window position allows the window to always be spawned at the center of the screen
    //This is more of quality of life, since the cursor is disabled, it would be annoying to have to move the screen around
    glfwSetWindowPos(window, 960 - (windowWidth/2), 540 - (windowHeight / 2));
    //Create a game variable
    Game game(window, windowWidth, windowHeight);
    //Start of the game loop
    game.start();

    //End of game loop, clean-up everything
    game.~Game();
    return 0;
}
