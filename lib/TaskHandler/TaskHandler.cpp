//
// Created by Nikita Rehemae on 27.11.2021.
//

#include "TaskHandler.h"

TaskHandler::TaskHandler(NewPing* leftSonar, NewPing* rightSonar) {
    globalState = new State;
    ls = leftSonar;
    rs = rightSonar;
}

UnsafeTask TaskHandler::Execute(ExecutionMessage* message) {
    TaskType task = message->type;
    globalState->Take(task);

    UnsafeTask exec_code = Successful;
    switch (task) {
        case ::ToNearEdge: {
            auto* serializedMessage = (ToNearEdgeMessage *)message;

            uint16_t velocity = serializedMessage->velocity();

            exec_code = ToNearEdge(velocity);
            break;
        }

        case ::ToEdge: {
            auto* serializedRequest = (ToEdgeMessage *)message;

            uint16_t velocity = serializedRequest->velocity();
            Direction direction = serializedRequest->direction();

            exec_code = ToEdge(velocity, direction);
            break;
        }

        case Released: {
            break;
        }

        case Error: {
            break;
        }
    }

    globalState->Release();
    return exec_code;
}

UnsafeTask TaskHandler::ToNearEdge(uint16_t velocity) {
    //By default, is left direction
    Direction direction = Negative;

    while (velocity == 0) { //If a user of the function used 0 for the value of velocity
        //Send request --> Output message on displays + Input from devices
        //Wait while a user input a number

        //mockup
        uint16_t valueFromUser = 5;
        velocity = valueFromUser;
    }

    uint64_t leftDistance = ls->ping_cm(); //Get the distance to the left edge
    uint64_t rightDistance = rs->ping_cm(); //Get the distance to the right edge

    if (rightDistance < leftDistance) {
        direction = Positive; //Change direction if the right edge is closer
    }
    ToEdgeMessage makeMoveRequest(&velocity, &direction); //Prepare task to the near edge in chosen direction
    UnsafeTask exec_code = Execute(&makeMoveRequest); //Execute the task

    return exec_code;
}

UnsafeTask TaskHandler::ToEdge(uint16_t velocity, Direction direction) {
    if (direction == Negative) return Successful;
    return Failure;
}

void TaskHandler::init() {
    startTime = millis();
}

TaskHandler::~TaskHandler() {
    delete [] globalState;
}
