#include <Arduino.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h>
#include <IRremote.h>

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define RECV_PIN 47

//left sonar
#define TRIG_PIN_L 43
#define ECHO_PIN_L 45

//right sonar
#define TRIG_PIN_R 39
#define ECHO_PIN_R 41

//init
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = { 23, 25, 27, 29 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 31, 33, 35, 37 }; //connect to the column pinouts of the keypad

struct States {
  enum type: byte {
    Released,
    ToNearEdge,
    ToEdge
  };

  States::type value;


};

//mockup
enum Sonars: byte {
    Left, 
    Right
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2);
States::type state;

inline float getDistanceFromSonar() __attribute__((always_inline));
inline float microsecondsToCentimeters() __attribute__((always_inline));

float microsecondsToCentimeters(int microseconds) {
  return microseconds / 29 / 2;
}

float getDistanceFromSonar(Sonars sonar) {
  long duration;
  float cm;

  if (sonar == Sonars::Right) {
    digitalWrite(TRIG_PIN_R, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_R, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN_R, LOW);
    duration = pulseIn(ECHO_PIN_R, HIGH);

    cm = microsecondsToCentimeters(duration);
  } else {
    digitalWrite(TRIG_PIN_L, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_L, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN_L, LOW);
    duration = pulseIn(ECHO_PIN_L, HIGH);

    cm = microsecondsToCentimeters(duration);
  }

  return cm;
}

byte MoveToNearEdge(float velocity) {
  enum Status: byte {
    Failure = 1,
    Successful = 0
  };

  while (velocity <= 0) {

  }

  return Status::Successful;
}

template<typename T> T GetNumberFromUser(String message) {

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //init lcd display
  lcd.init();
	lcd.backlight();

  //left sonar
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);

  //right sonar
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);

  //init state mode
  state = States::Released;
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = getDistanceFromSonar(Sonars::Left);
  Serial.print(distance);

  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}