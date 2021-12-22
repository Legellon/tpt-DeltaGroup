//
// Created by Nikita Rehemae on 27.11.2021.
//

#ifndef PHOTOSLIDER_TASKHANDLER_H
#define PHOTOSLIDER_TASKHANDLER_H

#include <State.h>
#include <NewPing.h>
#include <Stepper.h>
#include <LedControl.h>

#include <InterfaceController.h>

#define MAX_ARGS 10

#define STEPS_PER_REV 200

typedef enum {
    Successful, Failure,
} Executable;

typedef enum {
    UnknownDirection,
    Left, Right,
} Direction;


class ExecutionMessage {
public:
    Task task;

protected:
    void* args[MAX_ARGS];
};

class ToEdgeMessage : public ExecutionMessage {
public:
    explicit ToEdgeMessage(int16_t* velocity = new int16_t) : ExecutionMessage() {
        task = ::ToEdge;

        args[velocityPos] = velocity;
    }
    int16_t* velocity() { return static_cast<int16_t *>(args[velocityPos]); }

private:
    static const uint8_t velocityPos = 0;
};

class ToNearEdgeMessage : public ExecutionMessage {
public:
    explicit ToNearEdgeMessage(int16_t* velocity = new int16_t) : ExecutionMessage() {
        task = ::ToNearEdge;

        args[velocityPos] = velocity;
    }
    int16_t* velocity() { return static_cast<int16_t *>(args[velocityPos]); }

private:
    static const uint8_t velocityPos = 0;
};


class TaskHandler {
public:
    TaskHandler(NewPing* _leftSonic, NewPing* _rightSonic, LiquidCrystal_I2C* lcd);
    ~TaskHandler();

    void init();
    Executable Execute(ExecutionMessage* message);

private:
    uint64_t startTime{};

    State* globalState;

    NewPing* leftSonic;
    NewPing* rightSonic;
    Stepper* stepper;
    LiquidCrystal_I2C* lcd;

    Executable ToNearEdge(int16_t velocity);
    Executable ToEdge(int16_t velocity);
};

#endif //PHOTOSLIDER_TASKHANDLER_H
