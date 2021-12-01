//#include <iostream>
#include <Arduino.h>
#include <Wire.h>
#include <MD_MAX72xx.h>
#include <LiquidCrystal_I2C.h>
#include "DisplayClass.cpp"
//#include <Keypad.h>
//#include <MD_Parola.h>
//#include <SPI.h>
//#include <IRremote.h>

LiquidCrystal_I2C LCD(0x27, 16, 2);

DisplayClass dc(&LCD);

void setup()
{
    int len = dc.DisplayMessage(0);
}

void loop()
{
}