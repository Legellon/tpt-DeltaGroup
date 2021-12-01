//---CoreLibs---
#include <Arduino.h>
#include <TaskHandler.h>
//I2C / TWI
#include <Wire.h>
//Timing libs for Protothreads(A tool for imitation of something like multitasking)
#include <Chrono.h>
#include <LightChrono.h>

//---PeripheryLibs---
//Displays
#include <LiquidCrystal_I2C.h>  //For the adapter to LCD
//Input devices
#include <Keypad.h>
#include <IRremote.h>
//Sensors
#include <NewPing.h>            //Ultrasonic

//---HZLibs---
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define RECV_PIN 47  //IR port

//Size of the keypad

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

//Ports of the left ultrasonic

#define TRIG_PIN_L 43
#define ECHO_PIN_L 45

//Ports of the right ultrasonic

#define TRIG_PIN_R 39
#define ECHO_PIN_R 41

//init
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {                                         //Map of keypad values
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
static byte rowPins[KEYPAD_ROWS] { 23, 25, 27, 29 };                            //The row pin outs of the keypad
static byte colPins[KEYPAD_COLS] { 31, 33, 35, 37 };                            //The col pin outs of the keypad

Keypad KP(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);        //Keypad
LiquidCrystal_I2C LCD(0x27, 16, 2);                                             //LCD display
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

  //init LCD
  LCD.init();
  LCD.backlight();

  Master.init();
}

void loop() {
}