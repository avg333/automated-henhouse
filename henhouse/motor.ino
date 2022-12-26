

/**
 * @brief Initializes the pins used by the motor and their limit switches
 *
 */
void initMotorPins()
{
    pinMode(PIN_LIMIT_SWITCH_OPEN, INPUT);
    pinMode(PIN_LIMIT_SWITCH_CLOSE, INPUT);
    pinMode(PIN_SLEEP, OUTPUT);
    pinMode(PIN_STEP, OUTPUT);
    pinMode(PIN_DIRECTION, OUTPUT);

    digitalWrite(PIN_SLEEP, LOW);
    digitalWrite(PIN_STEP, LOW);
    digitalWrite(PIN_DIRECTION, LOW);
}

/**
 * @brief Moves the motor in the indicated direction until one of the limit switches is activated or it reaches the maximum steps
 *
 * @param motorMode = 1 OPEN, = 0 close
 * @return true if ERROR, false if OK
 */
bool actionMotor(int motorMode)
{
    digitalWrite(PIN_DIRECTION, motorMode);
    digitalWrite(PIN_SLEEP, HIGH);
    delay(INTIAL_DELAY);

    int steps = 0;

    const int pinLimitSwitch = getLimitSwitchPin(motorMode);
    while (digitalRead(pinLimitSwitch) == HIGH)
    {
        moveMotorOneStep();
        steps++;
        if (steps > MAX_STEPS)
        {
            disableEngine();
            return true;
        }
    }

    disableEngine();
    return false;
}

static void moveMotorOneStep()
{
    digitalWrite(PIN_STEP, HIGH);
    delay(STEP_PERIOD / 2);
    digitalWrite(PIN_STEP, LOW);
    delay(STEP_PERIOD / 2);
}

static void disableEngine()
{
    digitalWrite(PIN_STEP, LOW);
    digitalWrite(PIN_DIRECTION, LOW);
    digitalWrite(PIN_SLEEP, LOW);
}

static int getLimitSwitchPin(int motorMode)
{
    if (motorMode == MODE_CLOSE)
    {
        return PIN_LIMIT_SWITCH_CLOSE;
    }
    else
    {
        return PIN_LIMIT_SWITCH_OPEN;
    }
}