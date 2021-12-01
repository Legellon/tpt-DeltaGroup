//
// Created by Nikita Rehemae on 27.11.2021.
//

#ifndef PHOTOSLIDER_STATE_H
#define PHOTOSLIDER_STATE_H

#include <Arduino.h>

typedef enum: uint8_t {
    Released, ToNearEdge, ToEdge, Error
} TaskType;

class State {
public:
    State();

    TaskType current;

    void Take(TaskType task);
    void Release();

private:
    TaskType previous;
};

#endif //PHOTOSLIDER_STATE_H
