// Door opening configuration params
const float MIN_LUX_OPEN = 20;          // MIN LUXES TO OPEN DE DOOR
const float MAX_LUX_CLOSE = 2;          // MAX LUXES TO CLOSE DE DOOR
const int DELAY_BEFORE_CLOSE = 20 * 60; // SECONDS DELAY FROM CLOSED LUXES ARE REACHED UNTIL THE DOOR CLOSES

// PINS
const int PIN_SWITCH_MODE = 4;  // POSITIVE: MODE AUTO - NEGATIVE: MODE MANUAL
const int PIN_OPEN_BUTTON = 5;  // POSITIVE: CLOSE DOOR IF MODE = MANUAL
const int PIN_CLOSE_BUTTON = 6; // POSITIVE: OPEN DOOR IF MODE = MANUAL