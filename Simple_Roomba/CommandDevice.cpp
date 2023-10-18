#include "CommandDevice.h"

CommandDevice::CommandDevice(const std::vector<Commands>& commands) 
{
    m_commands = commands;
};

void CommandDevice::SeletRoomba(Roomba& roomba)
{
    currentRoomba = std::make_unique<Roomba>(roomba);
}

void CommandDevice::InterpretCommands()
{
    for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
    {
        //Interpret the command given a char
        switch (*it)
        {
            //Rotate the roomba clockwise or counterclockwise
            case RIGHT:
                currentRoomba->rotate(-90);
                break;
            case LEFT:
                currentRoomba->rotate(90);
                break;
            //Move the roomba forward or backwards
            case FORWARD:
                currentRoomba->move(1);
                break;
            case BACKWARD:
                currentRoomba->move(-1);
                break;
            default:
                break;
        }
    }
    
    currentRoomba->printPositionData();
}