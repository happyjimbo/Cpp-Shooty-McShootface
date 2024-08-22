#pragma once

#include "Command.h"
#include <queue>

class CommandQueue final
{
public:
    void push(const Command& command);
    Command pop();
    bool isEmpty() const;

private:
    std::queue<Command> mQueue;
};
