//---CoreLibs---
#include <Arduino.h>
//I2C / TWI
#include <Wire.h>
//Timing libs for Protothreads(A tool for imitation of something like multitasking)
#include <Chrono.h>
#include <LightChrono.h>

//---PeripheryLibs---
//Displays
#include <LiquidCrystal_I2C.h>  //For the adapter of LCD
//Input devices
#include <Keypad.h>
#include <IRremote.h>
//Sensors
#include <NewPing.h>  //Ultrasonic

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
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
static byte rowPins[KEYPAD_ROWS] { 23, 25, 27, 29 }; //The row pin outs of the keypad
static byte colPins[KEYPAD_COLS] { 31, 33, 35, 37 }; //The col pin outs of the keypad

enum class States: byte {
    Released,
    FatalError,
    ToNearEdge,
    ToEdge,
};

Keypad keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);    //Keypad
LiquidCrystal_I2C lcd(0x27, 16, 2);                                             //LCD display
NewPing LS(TRIG_PIN_L, ECHO_PIN_L);                                             //Left ultrasonic
NewPing RS(TRIG_PIN_R, ECHO_PIN_R);                                             //Right ultrasonic
States state;                                                                   //Global state of program (?)


byte ToEdge(bool direction, bool mockup = true) {
    //do some stuff
    byte exec_code = mockup ? 0 : 1;
    return exec_code;
}

byte ToNearEdge(uint32_t velocity) {
  enum Status: byte { //All planned outs from the function
      Successful = 0, Failure = 1
  };

  States prev_state = state; //Remember original state
  state = States::ToNearEdge; //Change a state on the state of function

  //By default, is left direction
  //False == left direction; True == right direction
  bool direction = false;

  while (velocity == 0) { //If a user of the function used 0 for the value of velocity
      //Send request --> Output message on displays + Input from devices
      //Wait while a user input a number
      uint32_t valueFromUser = 5; //mockup

      velocity = valueFromUser;
  }

  uint64_t leftDistance = LS.ping_cm(); //Get the distance to the left edge
  uint64_t rightDistance = RS.ping_cm(); //Get the distance to the right edge

  if (rightDistance < leftDistance) {
      direction = true; //Change direction if a right edge is closer
  }
  byte exec_code = ToEdge(direction); //Start move to the near edge in the chosen direction

  state = prev_state; //Revert to the original state before calling the function

  if (exec_code == 0) return Status::Failure;
  return Status::Successful;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //init LCD
  lcd.init();
  lcd.backlight();

  //define left sonar
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);

  //define right sonar
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);

  //init state mode
  state = States::Released;
}

void loop() {
//    unsigned long left = LS.ping_cm();
//    unsigned long right = RS.ping_cm();
//
//    bool direction = false;
//
//    Serial.print("LS = ");
//    Serial.print(left);
//    Serial.print(" RS = ");
//    Serial.print(right);
//    Serial.println();
//
//    if(right > left) {
//        direction = true;
//    }
//
//    Serial.println(direction);
//
//    delay(2000);
    if (keypad.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( keypad.key[i].stateChanged )   // Only find keys that have changed state.
            {
                Serial.print("Key ");
                Serial.print(keypad.key[i].kchar);
                Serial.println();
            }
        }
    }
}