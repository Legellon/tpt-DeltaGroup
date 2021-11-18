#include <Arduino.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h> // lcd 16 02
#include <Keypad.h> // membrannaja klava

// maxon
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// pult
#include <IRremote.h>

#define RECV_PIN 47

IRrecv irrecv(RECV_PIN);
decode_results results;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37 }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();

  lcd.clear();
	lcd.setCursor(4,0);
	lcd.print("Hackster");
  
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}