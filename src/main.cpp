#include <Arduino.h>
#include <NewPing.h>
#include <TaskHandler.h>
#include <Wire.h>

#include <MD_MAX72xx.h>

#define IR_PIN 47

#define TRIG_PIN_L 43
#define ECHO_PIN_L 45

#define TRIG_PIN_R 39
#define ECHO_PIN_R 41

NewPing LS(TRIG_PIN_L, ECHO_PIN_L);                                             //Left ultrasonic
NewPing RS(TRIG_PIN_R, ECHO_PIN_R);                                             //Right ultrasonic
TaskHandler Master(&LS, &RS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //define left sonar
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);

  //define right sonar
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);

  Master.init();
}

void loop() {
  
}