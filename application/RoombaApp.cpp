#include "RoombaApp.h"
#include <iostream>
#include <string>

#include "../utils/Vector2.h"
#include "../utils/InputHandler.h"
#include "../roomba/Roomba.h"
#include "../roomba/CommandDevice.h"

void RoombaApp::Run() 
{
    std::cout << "This is a roomba service, to function I ask you to fill in some information.\n";

    RoombaData rbData;
    InputHandler::HandleRoombaInputs(rbData);
    //Now all the inputs are finished and checks whether they are invalid have been made

    //Now we can create the roomba and give it the starting values
    Roomba roomba(rbData);

    CommandDevice commandDevice(rbData.commands);
    commandDevice.SeletRoomba(roomba);
    commandDevice.InterpretCommands();
}