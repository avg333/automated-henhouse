// Modes
const int MODE_OPEN = HIGH; // POSITIVE: ROTATION CLOCKWISE
const int MODE_CLOSE = LOW; // NEGATIVE: ROTATION COUNTERCLOCKWISE

// Pins
const int PIN_LIMIT_SWITCH_OPEN = 7;  // LOW WHEN IS FULL OPEN
const int PIN_LIMIT_SWITCH_CLOSE = 8; // LOW WHEN IS FULL CLOSE
const int PIN_SLEEP = 10;             // DISABLES ENGINE WHILE NOT RUNNING
const int PIN_STEP = 11;              // MOVE THE MOTOR 1 STEP
const int PIN_DIRECTION = 12;         // POSITIVE: MODE_OPEN - NEGATIVE: MODE_CLOSE

/*
   NEMA 17HS4401 - A4988
   1.7A (12V) 1.5ohm
   Coil voltage: 1,7*1,15=1,955V
   Vref = 1,7 * (8 x 0,1) * 70% = 0.952
   1,8º per step -> 200 steps per revolution
*/
// Screw data
const int SCREW_PITCH = 8; // Screw pitch distance in mm
// Distance data
const int TOTAL_DISTANCE = 300; // Total distance in mm
// Motor configuration params
const int INTIAL_DELAY = 1000;                              // Waiting time from the request to activate the motor until it starts to rotate
const int RPM = 30;                                         // Speed in rpm
const int TOTAL_REVOLUTIONS = TOTAL_DISTANCE / SCREW_PITCH; // Revolutions needed to travel the desired distance
const int SAFE_REV_RANGE = 5;                               // Turns higher than necessary before stopping the engine
// Motor data
const int STEPS_PER_REVOLUTION = 200;                                              // Steps per revolution
const int STEP_PERIOD = 3 / 20 * RPM * 1000;                                       // Period between steps, derived from RPM, in ms
const int MAX_STEPS = STEPS_PER_REVOLUTION * (TOTAL_REVOLUTIONS + SAFE_REV_RANGE); // Maximum steps to stop the motor for safety