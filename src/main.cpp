#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <IRremote.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // init lcd
  lcd.begin(16, 2);
  // turn on the backlight
  lcd.backlight();
}

void loop() {
  // clear lcd
  lcd.clear();
  // set cursor to the begining of the lcd
  lcd.setCursor(0, 1);
  // print message
  lcd.print("Hello");
}