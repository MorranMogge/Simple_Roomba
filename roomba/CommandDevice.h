#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Roomba.h"

//CommandDevice can be thought of as an app on your phone,
//where you can select a roomba and tell it what to do
class CommandDevice
{
private:
    std::vector<Commands> m_commands;
    std::unique_ptr<Roomba> currentRoomba;

public:
    CommandDevice(const std::vector<Commands>& commands);

    void SeletRoomba(Roomba& roomba);
    void InterpretCommands();
};