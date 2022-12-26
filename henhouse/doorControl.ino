
#include "motor.h"
#include "doorControl.h"
#include <BH1750.h>

BH1750 lightMeter;

void initOperationPinsAndLightMeter()
{
    lightMeter.begin();
    pinMode(PIN_SWITCH_MODE, INPUT);
    pinMode(PIN_OPEN_BUTTON, INPUT);
    pinMode(PIN_CLOSE_BUTTON, INPUT);
}

void doorControl()
{
    if (digitalRead(PIN_SWITCH_MODE) == HIGH)
    {
        modeAuto();
    }
    else
    {
        modeManual();
    }
}

static void modeAuto()
{
    const float lux = lightMeter.readLightLevel();
    if (lux > MIN_LUX_OPEN && !isOpen())
        openDoor();
    else if (lux < MAX_LUX_CLOSE && !isClose())
    {
        delay(DELAY_BEFORE_CLOSE);
        closeDoor();
    }
}

static void modeManual()
{
    if (digitalRead(PIN_OPEN_BUTTON) == HIGH && !isOpen())
    {
        openDoor();
    }
    else if (digitalRead(PIN_CLOSE_BUTTON) == HIGH && !isClose())
    {
        closeDoor();
    }
}

static bool isOpen()
{
    return digitalRead(PIN_LIMIT_SWITCH_OPEN) == LOW;
}

static bool isClose()
{
    return digitalRead(PIN_LIMIT_SWITCH_CLOSE) == LOW;
}

static void openDoor()
{
    if (actionMotor(MODE_OPEN))
    {
        error();
    }
}

static void closeDoor()
{
    if (actionMotor(MODE_CLOSE))
    {
        error();
    }
}

static void error()
{
    while (true)
    {
        // TODO Añadir iluminacion led
        delay(1000);
    }
}