#include <iostream>
#include <string>
#include "Vector2.h"

bool checkForCorrectInput(const std::string& input, char delimiter, Vector2& output)
{
    int sizeOfString = input.size();
    
    std::string widthInput = "";
    std::string heightInput = "";
    
    int widthOrHeight = 0;

    for (int i = 0; i < sizeOfString; i++)
    {
        //Delimiter is used to divide up the numbers to two seperate
        if (input[i] == delimiter)
            widthOrHeight++;
        //Converts the string to ASCII values, easier to check if they are numbers this way
        //This also removes the ability to write negative numbers, sinze the ascii code of "-" is not included
        else if ((int)input[i] > 48 && (int)input[i] < 58)
        {
            if (widthOrHeight == 0)
                widthInput += input[i];
            else
                heightInput += input[i];
        }
        else
        {
            //In case we see invalid characters such as j, we send an error message
            std::cout << "Invalid input: [" << input << "]\n Expected two nubers\n";
            return false;
        }
    }

    int xValue = std::stoi(widthInput);
    if (xValue < 1)
    {
        std::cout << "Value can not be smaller than 1, you input " << xValue << " try again\n";
        return false;
    }
    int yValue = std::stoi(heightInput);
    if (xValue < 1)
    {
        std::cout << "Value can not be smaller than 1, you input " << yValue << " try again\n";
        return false;
    }

    output.x = xValue;
    output.y = yValue;

    return true;
}

bool checkForValidPosition(Vector2 position, Vector2 roomSize)
{
    if (position.x < 1 || position.y < 1 ||position.x > roomSize.x || position.y > roomSize.y)
    {
        std::cout << "Invalid position: (" << position.x << "x" << position.y << ")\n";
        return false;
    }
    return true;
}

int main()
{
    std::cout << "This is a roomba service, to function I ask you to fill in some information.\n";
   
    
    Vector2 roomSize;
    Vector2 startPosition;

    std::string roomSizeInput;
    std::string startPositionInput;
    std::string startDirectionInput;
    std::string commands;
    
    bool roomSizeFinished = false;
    while (!roomSizeFinished)
    {
        std::cout << "Enter the size of your room in meters, fill in by typing for example 8x4\n";
        std::getline(std::cin, roomSizeInput);

        roomSizeFinished = checkForCorrectInput(roomSizeInput, 'x', roomSize);
    }

    bool startPosFinished = false;
    while (!startPosFinished)
    {
        std::cout << "Enter the start position of your roomba, fill in by typing for example 1x2\n";
        std::getline(std::cin, startPositionInput);

        startPosFinished = checkForCorrectInput(startPositionInput, 'x', startPosition);
        if (startPosFinished)
            startPosFinished = checkForValidPosition(startPosition, roomSize);
    }

    bool startDirectionFinished = false;
    while (!startDirectionFinished)
    {
        std::cout << "Enter the starting direction of your roomba, fill in by typing w, d, s or a\n";
        std::getline(std::cin, startDirectionInput);
        if (startDirectionInput == "w" || startDirectionInput == "d" || startDirectionInput == "s" || startDirectionInput == "a")
            startDirectionFinished = true;
        else
        {
            std::cout << "Invalid input: [" << startDirectionInput << "]\n Expected either w, d, s or a\n";
        }
    }

    bool commandsFinished = false;
    while (!commandsFinished)
    {
        commandsFinished = true;

        std::cout << "Enter the commands your roomba, fill in by typing a string containing w, d, s or a\n";
        std::getline(std::cin, commands);
        int commandSize = commands.size();
        for (int i = 0; i < commandSize && commandsFinished; i++)
        {
            if (commands[i] != 'w' && commands[i] != 'd' && commands[i] != 's' && commands[i] != 'a')
            {
                std::cout << "Invalid input: [" << commands[i] << "]\n Expected either w, d, s or a\n";
                commandsFinished = false;
            }
        }
    }

    //Now all the inputs are finished and check to be invalid

}
