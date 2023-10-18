#include "RoombaApp.h"
#include <iostream>
#include <string>
#include "Vector2.h"
#include "Roomba.h"
#include "InputHandler.h"

bool checkForValidPosition(Vector2 position, Vector2 roomSize)
{
    //In case it goes out of bounds, we write an error message and return false
    if (position.x < 1 || position.y < 1 ||position.x > roomSize.x || position.y > roomSize.y)
    {
        std::cout << "Invalid position: [" << position.x << "x" << position.y << "]\nRoomba is outside of room (" << roomSize.x << "x" << roomSize.y << ")\n";
        return false;
    }
    return true;
}

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

    std::string commands;
    
    //Now we start taking inputs from the user
    InputHandler::HandleSizeAndPositionInput("Enter the size of your room in meters, fill in by typing for example 8x4\n", roomSize);

    //Start position also need to be checked whether it is inside the room
    bool validStartposition = false;
    while (!validStartposition)
    {
        InputHandler::HandleSizeAndPositionInput("Enter the start position of your roomba, fill in by typing for example 4x2\n", startPosition);
        validStartposition = checkForValidPosition(startPosition, roomSize);
    }
     
    InputHandler::HandleDirectionInput("Enter the starting direction of your roomba, fill in by typing w, e, s or n\n");
    InputHandler::HandleCommandsInput("Enter the commands your roomba, fill in by typing a string containing w, d, s or a\n", commands);
    //Now all the inputs are finished and checks whether they are invalid have been made

    std::cout << "Starting roomba: Executing commands: [" + commands + "]\n";
    //Now we can create the roomba and give it the starting values
    Roomba roomba;

    int index = 0;
    int commandSize = commands.size();
    while (index < commandSize)
    {
        //Send the command from the list to the roomba and increase the index for the next loop
        roomba.interpretCommand(commands[index++]);

        //Checks whether the roomba is out of bounds, and if it is then cancel the loop
        if (!checkForValidPosition(roomba.getPosition(), roomSize))
            break;
        //Else write the current position of the roomba
        else
            std::cout << "Position: (" << (int)roomba.getPosition().x << "x" << (int)roomba.getPosition().y << ") " 
            << "Direction: (" << (int)roomba.getDirection().x << ", " << (int)roomba.getDirection().y << ")\n";
    }
}