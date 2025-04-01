#pragma once

#define FINISH_LINE 5000

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

enum ALL_NP_OBJ_IDX {
    GST1_IDX_KL = 0,
    GST1_IDX_WL,
    GST1_IDX_WC,

    GST2_IDX_KL,
    GST2_IDX_WL,
    GST2_IDX_WC,

    ROAD_PLANE,

    LIGHT_BALL1,
    LIGHT_BALL2,
    LIGHT_BALL3
};

enum ACTIVE_CAM {
    THIRD_PERSON = 0,
    FIRST_PERSON
};

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
    COVER
};

enum MOVE {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};
