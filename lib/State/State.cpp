//
// Created by Nikita Rehemae on 27.11.2021.
//

#include "State.h"

State::State() {
    current = Released;
    previous = current;
}

void State::Take(TaskType task) {
    previous = current;
    current = task;
}

void State::Release() {
    TaskType mem = current;
    current = previous;
    previous = mem;
}
