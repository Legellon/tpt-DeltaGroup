//
// Created by Nikita Rehemae on 27.11.2021.
//

#ifndef PHOTOSLIDER_TASKHANDLER_H
#define PHOTOSLIDER_TASKHANDLER_H

#include <State.h>
#include <NewPing.h>

#define MAX_ARGS_LENGTH 10

typedef enum: uint8_t {
    Successful, Failure,
} UnsafeTask;

//Negative == Left direction; Positive == Right direction
typedef enum: bool {
    Negative, Positive
} Direction;


class ExecutionMessage {
public:
    TaskType type;
    
protected:
    void* args[MAX_ARGS_LENGTH];
};

class ToNearEdgeMessage : public ExecutionMessage {
public:
    explicit ToNearEdgeMessage(uint16_t* velocity) : ExecutionMessage() {
        type = TaskType::ToNearEdge;
        args[0] = velocity;
    }

    uint16_t velocity() {
        return *(uint16_t *)args[0];
    }
};

//example
class ToEdgeMessage : public ExecutionMessage {
public:
    ToEdgeMessage(uint16_t* velocity, Direction* direction) : ExecutionMessage() {
        type = TaskType::ToEdge;
        args[0] = velocity;
        args[1] = direction;
    }

    uint16_t velocity() {
        return *(uint16_t *)args[0];
    }

    Direction direction() {
        return *(Direction *)args[1];
    }
};


class TaskHandler {
public:
    TaskHandler(NewPing* leftSonar, NewPing* rightSonar);
    ~TaskHandler();

    void init();
    UnsafeTask Execute(ExecutionMessage* message);

private:
    uint64_t startTime{};

    State* globalState;
    NewPing* ls;
    NewPing* rs;

    UnsafeTask ToNearEdge(uint16_t velocity = 0);
    UnsafeTask ToEdge(uint16_t velocity, Direction direction);
};

#endif //PHOTOSLIDER_TASKHANDLER_H
