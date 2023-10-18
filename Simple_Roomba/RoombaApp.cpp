#include "RoombaApp.h"
#include <iostream>
#include <string>
#include "Vector2.h"
#include "Roomba.h"
#include "InputHandler.h"
#include "CommandDevice.h"

RoombaApp::RoombaApp() 
{

}

RoombaApp::~RoombaApp() 
{

}

void RoombaApp::Run() 
{
    std::cout << "This is a roomba service, to function I ask you to fill in some information.\n";
    
    Vector2 roomSize;
    Vector2 startPosition;

    RoombaData rbData;
    InputHandler::HandleRoombaInputs(rbData);

    //Now all the inputs are finished and checks whether they are invalid have been made

    //Now we can create the roomba and give it the starting values
    CommandDevice commandDevice(rbData.commands);
    Roomba roomba(rbData);

    commandDevice.SeletRoomba(roomba);
    commandDevice.InterpretCommands();
}