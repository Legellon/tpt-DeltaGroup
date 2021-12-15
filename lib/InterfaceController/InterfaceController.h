//
// Created by Nikita Rehemae on 02.12.2021.
//

#ifndef PHOTOSLIDER_INTERFACECONTROLLER_H
#define PHOTOSLIDER_INTERFACECONTROLLER_H

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
//#include <IRremote.h>

typedef enum {
    InputVelocity = 0, MovingPlatform = 1,
} MessageID;

static char keys[KEYPAD_ROWS][KEYPAD_COLS] = {                                  //Map of keypad values
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};
static byte rowPins[KEYPAD_ROWS] { 23, 25, 27, 29 };                            //The row pin outs of the keypad
static byte colPins[KEYPAD_COLS] { 31, 33, 35, 37 };                            //The col pin outs of the keypad

class InterfaceController {
public:
    InterfaceController();

    void init();
    void DisplayHeader(MessageID messageId);
    int GetNumber();
    char GetKey();

private:
    const char* lcdMessages[2] = {
            "Input a velocity of the platform:",
            "The platform is moving to the destination...",
    };

    uint64_t startTime{};
    LiquidCrystal_I2C* lcd;
    Keypad* kp;

    void OutputString(const char* string, uint8_t line);
    int MoveStringForward(char* string, uint8_t line);
};

#endif //PHOTOSLIDER_INTERFACECONTROLLER_H
