#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  initOperationPinsAndLightMeter();
  initMotorPins();
}

void loop()
{
  doorControl();
}
