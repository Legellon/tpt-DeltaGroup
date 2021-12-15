//
// Created by Nikita Rehemae on 27.11.2021.
//

#ifndef PHOTOSLIDER_STATE_H
#define PHOTOSLIDER_STATE_H

#include <Arduino.h>

typedef enum {
    Released, ToNearEdge, ToEdge, ErrorHandle
} Task;

class State {
public:
    State();

    Task current;

    void Take(Task task);
    void Release();

private:
    Task previous;
};

#endif //PHOTOSLIDER_STATE_H
