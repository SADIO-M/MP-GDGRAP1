#pragma once

/*
    This is an enumerations and defintions header file
       - Allows ease of use and readablity for the enumerations used throughout the code
*/

//Finish line coordinate
#define FINISH_LINE 1500

/* LEGEND:
    - PLYR : Player
    - GST# : Ghost, then number at the end
    - IDX : Index
    - KL : Kart Livery
    - WL : Wheel
    - WC : Wheel Cover
*/
enum PLYR_KART_PARTS {
    PLYR_IDX_KL = 0,
    PLYR_IDX_WL,
    PLYR_IDX_WC,
};

//All non-player objects indices (ease of use for accessing in the all objects vector)
enum ALL_NP_OBJ_IDX {
    //Ghost Kart 1
    GST1_IDX_KL = 0,
    GST1_IDX_WL,
    GST1_IDX_WC,
    //Ghost Kart 2
    GST2_IDX_KL,
    GST2_IDX_WL,
    GST2_IDX_WC,
    //Road
    ROAD_PLANE,
    //Light Ball (Signal lights at the start)
    LIGHT_BALL1,
    LIGHT_BALL2,
    LIGHT_BALL3,
    //Finish Line
    FINISH_PLANE,
    //Normal mapped landmarks (townhouse)
    TOWNHOUSE1,
    TOWNHOUSE2,
    TOWNHOUSE3,
    TOWNHOUSE4,
    TOWNHOUSE5,
    //Normal mapped landmarks (stone house)
    STONE_HOUSE1,
    STONE_HOUSE2,
    STONE_HOUSE3,
    STONE_HOUSE4,
    STONE_HOUSE5
};

//Selecting the active camera
enum ACTIVE_CAM {
    THIRD_PERSON = 0,
    FIRST_PERSON
};

//Driving controls
enum DRIVING {
    ACCELERATE = 0,
    REVERSE,
    STEER_R,
    STEER_L
};

//To know if it should unbind, bind, or generate a VAO
enum VAO_BINDING {
    UNBIND = 0,
    BIND,
    GENERATE,
};

//To know what texture needs to be loaded
enum SELECT_TEXTURE {
    NIGHT = 0,
    MORNING,
    LIVERY,
    WHEEL,
    COVER,
    TOWNHOUSE_COLOR,
    TOWNHOUSE_NORM,
    STONE_HOUSE_COLOR,
    STONE_HOUSE_NORM
};

//To switch the color of the point light (and the spot light by extension)
enum POINT_LIGHT_COLOR {
    NONE = 0,
    RED,
    YELLOW,
    GREEN,
    WHITE
};

//Movement of other objects
enum MOVE {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};
