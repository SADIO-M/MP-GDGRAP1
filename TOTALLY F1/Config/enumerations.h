#pragma once

/* LEGEND:
    - PLYR : Player
    - GST# : Ghost, then number at the end
    - IDX : Index
    - KL : Kart Livery
    - WL : Wheel
    - WC : Wheel Cover
*/
enum ALL_OBJ_IDX {
    PLYR_IDX_KL = 0,
    PLYR_IDX_WL,
    PLYR_IDX_WC,

    GST1_IDX_KL,
    GST1_IDX_WL,
    GST1_IDX_WC,

    GST2_IDX_KL,
    GST2_IDX_WL,
    GST2_IDX_WC,
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
};

//To know which arrow key is being pressed
enum ARROW_KEYS {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};
