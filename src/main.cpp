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

Keypad keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);    //Keypad
LiquidCrystal_I2C lcd(0x27, 16, 2);                   //LCD display
NewPing LS(TRIG_PIN_L, ECHO_PIN_L);                                             //Left ultrasonic
NewPing RS(TRIG_PIN_R, ECHO_PIN_R);                                             //Right ultrasonic
//State state = {State::Released};                                              //Global state of program (?)


byte ToEdge(bool direction) {
    //do some stuff
    return 0;
}


byte ToNearEdge(uint32_t velocity) {
  enum Status: byte {
      Successful = 0, Failure = 1
  };

  //By default, is left direction
  //False == left direction; True == right direction
  bool direction = false;

  while (velocity <= 0) { //If a user of the function used zero for the value of velocity
      //Send request --> Output message on displays + Input form devices
      //Wait while a user input a number
      uint32_t valueFromUser = 5; //mockup
      
      velocity = valueFromUser;
  }

  uint64_t leftDistance = LS.ping_cm(); //Get the distance to the left edge
  uint64_t rightDistance = RS.ping_cm(); //Get the distance to the right edge

  if (rightDistance < leftDistance) {
      direction = true; //Change direction if a right edge is closer
  }
  byte exec_code = ToEdge(direction);

  if (exec_code == 0) return Status::Failure;

  return Status::Successful;
}




class State {
public: //methods
    enum class type: byte {
        Released,
        FatalError,
        ToNearEdge,
        ToEdge,
    };

    State() = default;

    type current;

    void init() {
        current = type::Released;
        previous = current;
    }

    void take(type task) {
        previous = current;
        current = task;
    }

    void release() {
        type temp = current;
        current = previous;
        previous = temp;
    }

private:
    type previous;

};


//prototype
class StateController {
public:
    static byte execute(State *state, State::type task) {
        state->take(task);



        state->release();
    }

private:
};


//prototype
class DisplayController {
public:
    DisplayController() = default;

    void OutputHeaderMessage() {}

private:
//    const char *Messages[] {
//            "Input a velocity of the platform:",
//            "The platform is moving to the destination...",
//    };
    enum MessageID: byte;

};

//prototype
class InputController {
public:
    InputController() = default;

    template<class Type> Type GetNumber() {}

private:


};

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
}

void loop() {
    byte exec_code = ToNearEdge(0);
}