//
// Created by Nikita Rehemae on 02.12.2021.
//

#ifndef PHOTOSLIDER_INTERFACECONTROLLER_H
#define PHOTOSLIDER_INTERFACECONTROLLER_H

typedef enum: int {
    InputVelocity = 0,
    MovingPlatform = 1,
} MessageID;

const char* Messages[] = {
        "Input a velocity of the platform:",
        "The platform is moving to the destination...",
};

class InterfaceController {
public:
    void DisplayLCDHeader(MessageID message_id) {
        auto message = Messages[message_id];
//        outputLCDData(message);

//            sleep(3);

//            size_t length = strlen(message) - 16;
//            for (int i = 0; i < length; i++) {
//                message++;
//                outputLCDData(message);
//                usleep(300000);
//            }
    }

private:

};

#endif //PHOTOSLIDER_INTERFACECONTROLLER_H
