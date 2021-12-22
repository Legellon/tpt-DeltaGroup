//
// Created by Nikita Rehemae on 27.11.2021.
//

#include "TaskHandler.h"

TaskHandler::TaskHandler(NewPing* _leftSonic, NewPing* _rightSonic) {
    globalState = new State;

    leftSonic   = _leftSonic;
    rightSonic  = _rightSonic;
    stepper     = new Stepper(200, 4, 5, 6, 7);
}

TaskHandler::~TaskHandler() {
    delete globalState;
    delete stepper;
}

void TaskHandler::init() {
    startTime = millis();
    stepper->setSpeed(60);
    ui.init();
}

Executable TaskHandler::Execute(ExecutionMessage* message) {
    Task task = message->task;
    globalState->Take(task);

    Executable exec_code = ::Successful;
    switch (task) {
        case ::ToEdge: {
            auto deserializedMessage = reinterpret_cast<ToEdgeMessage *>(message);
            exec_code = ToEdge(
                    *deserializedMessage->velocity()
                    );
        } break;
        case ::ToNearEdge: {
            auto deserializedMessage = reinterpret_cast<ToNearEdgeMessage *>(message);
            exec_code = ToNearEdge(
                    *deserializedMessage->velocity()
                    );
        } break;
        case ::Released: {
        } break;
        case ::ErrorHandle: {
        } break;
    }

    globalState->Release();
    return exec_code;
}

Executable TaskHandler::ToEdge(int16_t velocity) {
    Executable exec_code = Successful;
    NewPing* workingSonic;

    Direction direction =
            velocity == 0 ? UnknownDirection
            : velocity < 0 ? Left
            : Right;

    if (direction == UnknownDirection) 
    {
        while (direction == UnknownDirection) {
            char key = ui.GetKey();
            direction =
                    key == '1' ? Right
                    : key == '2' ? Left
                    : UnknownDirection;
        }

        while (velocity == 0) {
//            velocity = ui.GetNumber();
            velocity = STEPS_PER_REV; //mockup
        }

        velocity = direction == Left ? -abs(velocity) : abs(velocity);
    }

    workingSonic = direction == Left ? leftSonic : rightSonic;

    //LCD сообщение, которое отображает направление движения тележки

    uint16_t distance;
    do { //Movement
        stepper->step(velocity);
        distance = workingSonic->ping_cm();
    } while (distance >= 10);

    //Отчистить LCD экран

    return exec_code;
}

Executable TaskHandler::ToNearEdge(int16_t velocity) {
    Executable exec_code = Successful;

    uint16_t leftDistance = leftSonic->ping_cm(); //Get the distance to the left edge
    uint16_t rightDistance = rightSonic->ping_cm(); //Get the distance to the right edge

    velocity = abs(velocity);

    if (leftDistance < rightDistance) velocity = -velocity;

    exec_code = Execute(new ToEdgeMessage(&velocity)); //Make a move to the chosen edge

    return exec_code;
}
