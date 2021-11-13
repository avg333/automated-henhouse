#include <Wire.h>
#include <BH1750.h>

/*
   NEMA 17HS4401 - A4988
   1.7A (12V) 1.5ohm
   Voltaje bobina: 1,7*1,15=1,955V
   Vref = 1,7 * (8 x 0,1) * 70% = 0.952
   1,8º por paso -> 200 pasos por vuelta
*/

// PINES
const int pinSwitchAutoMode = 4;  // CUANDO SE PRESIONA PASA A HIGH
const int pinOpenButton = 5;  // CUANDO SE PRESIONA PASA A HIGH
const int pinCloseButton = 6;  // CUANDO SE PRESIONA PASA A HIGH
const int pinLimitOpenSwitch = 7;  // CUANDO SE PRESIONA PASA A LOW
const int pinLimitCloseSwitch = 8;  // CUANDO SE PRESIONA PASA A LOW

const int pinSleep = 10; // DESHABILITA EL MOTOR MIENTRAS NO ESTA EN FUNCIONAMIENTO
const int pinStep = 11; // MUEVE EL MOTOR
const int pinDir = 12; // ESTABLECE LA DIRECCION EN LA QUE SE MUEVE EL MOTOR

// LUMENES APERTURA
const float luxOpen = 20; // LUX A LOS QUE SE ABRE LA PUERTA
const float luxClose = 2; // LUX A LOS QUE SE CIERRA LA PUERTA
const int delayClose = 20; // Minutos que espera el motor para cerrar

// VALORES MOTOR
const int MODE_OPEN = HIGH;
const int MODE_CLOSE = LOW;
const int PASOS_POR_VUELTA = 200; // Pasos por vuelta de nuestro motor
const int RPM = 30; // Velocidad en RPM
const int PERIODO_PASO = 4; // Periodo entre pasos, derivado de las RPM
const int VUELTAS_TOTALES = 35; // Vueltas necesarias para recorrer 30cm
const int MAX_STEPS = PASOS_POR_VUELTA * (VUELTAS_TOTALES + 5); // Pasos hasta desconectar el motor

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  
  pinMode(pinSwitchAutoMode, INPUT);
  pinMode(pinOpenButton, INPUT);
  pinMode(pinCloseButton, INPUT);
  pinMode(pinLimitOpenSwitch, INPUT);
  pinMode(pinLimitCloseSwitch, INPUT);
  pinMode(pinSleep, OUTPUT);
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  
  digitalWrite(pinSleep, LOW);
  digitalWrite(pinStep, LOW);
  digitalWrite(pinDir, LOW);
}

void loop() {
  int stateSwitchAutoMode = digitalRead(pinSwitchAutoMode);
  int stateLimitOpenSwitch = digitalRead(pinLimitOpenSwitch);
  int stateLimitCloseSwitch = digitalRead(pinLimitCloseSwitch);

  if (stateSwitchAutoMode == HIGH){
    float lux = lightMeter.readLightLevel();
    if (lux > luxOpen && stateLimitOpenSwitch == HIGH)
      actionMotor(MODE_OPEN);
    else if (lux < luxClose && stateLimitCloseSwitch == HIGH){
      delay(delayClose * 60);
      actionMotor(MODE_CLOSE);
    }
    
  } else {
    int stateOpenButton = digitalRead(pinOpenButton);
    int stateCloseButton = digitalRead(pinCloseButton);
    if (stateOpenButton == HIGH && stateLimitOpenSwitch == HIGH)
      actionMotor(MODE_OPEN);
    else if (stateCloseButton == HIGH && stateLimitCloseSwitch == HIGH)
      actionMotor(MODE_CLOSE);   
  }
  
}

void actionMotor(int motorMode) {
  digitalWrite(pinDir, motorMode);
  digitalWrite(pinSleep, HIGH);
  int pinLimitSwitch = pinLimitOpenSwitch;
  if (motorMode == MODE_CLOSE)
    pinLimitSwitch = pinLimitCloseSwitch;
  int stateLimitSwitch = digitalRead(pinLimitSwitch);
  delay(1000);
  int steps = 0;

  while (stateLimitSwitch == HIGH) {
    digitalWrite(pinStep, HIGH);
    delay(PERIODO_PASO / 2);
    digitalWrite(pinStep, LOW);
    delay(PERIODO_PASO / 2);
    stateLimitSwitch = digitalRead(pinLimitSwitch);
    steps++;
    if (steps > MAX_STEPS)
      error();
  }

  digitalWrite(pinDir, LOW);
  digitalWrite(pinSleep, LOW);
}

void error(){
  digitalWrite(pinStep, LOW);
  digitalWrite(pinDir, LOW);
  digitalWrite(pinSleep, LOW);
  while (true){
    delay(1000);
  }
  
}
