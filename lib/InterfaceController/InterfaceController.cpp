//
// Created by Nikita Rehemae on 02.12.2021.
//

#include "InterfaceController.h"

InterfaceController::InterfaceController() {
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    kp = new Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
}

void InterfaceController::OutputString(const char *string, uint8_t line) {
    lcd->setCursor(0, line);
    lcd->printstr(string);
}

int InterfaceController::MoveStringForward(char* string, uint8_t line) {
//    PT_BEGIN(pt);
//
//    for (size_t i = strlen(string); i > 16;) {
//        if(startTime - millis() >= 250) {
//            string++;
//            OutputString(string, line);
//            i--;
//        }
//    }
//
//    PT_END(pt);
}

void InterfaceController::DisplayHeader(MessageID messageId) {
    char* message = const_cast<char *>(lcdMessages[messageId]);
    OutputString(message, 0);
    MoveStringForward(message, 0);
}

void InterfaceController::init() {
    lcd->init();
    lcd->backlight();
    startTime = millis();
}

int InterfaceController::GetNumber() {

    return 0;
}

char InterfaceController::GetKey() {
    char key;
    for(;;) {
        key = kp->getKey();
        if (key) break;
    }
    return key;
}
