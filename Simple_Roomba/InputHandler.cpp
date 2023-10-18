#include "InputHandler.h"
#include <iostream>

bool IsNumber(char character)
{

    //Converts the string to ASCII values, easier to check if they are numbers this way
    int ASCIIvalue = static_cast<int>(character);
    int lowerLimit = static_cast<int>('0');
    int upperLimit = static_cast<int>('9');

    //This also removes the ability to write negative numbers, sinze the ascii code of "-" is not included
    return ASCIIvalue >= lowerLimit && ASCIIvalue <= upperLimit;
}

bool positionIsValid(Vector2 position, Vector2 roomSize)
{
    //In case it goes out of bounds, we write an error message and return false
    if (position.x < 1 || position.y < 1 ||position.x > roomSize.x || position.y > roomSize.y)
    {
        std::cout << "Invalid position: [" << position.x << "x" << position.y << "]\nRoomba is outside of room (" << roomSize.x << "x" << roomSize.y << ")\n";
        return false;
    }
    return true;
}

Commands convertCharToCommand(char character)
{
    Commands cmd = Commands::FORWARD;

    switch (character)
    {
    case 'w':
        cmd = Commands::FORWARD;
        break;
    case 's':
        cmd = Commands::BACKWARD;
    case 'a':
        cmd = Commands::LEFT;
    case 'd':
        cmd = Commands::RIGHT;
    default:
        cmd = Commands::FORWARD;
        break;
    }

    return cmd;
}

int convertCharToRotation(char character)
{
    int rotation = 0;
    //Set the rotation
	switch (character)
	{
		case 'e':
			rotation = 0;
			break;
		case 'n':
			rotation = 90;
			break;
		case 'w':
			rotation = 180;
			break;
		case 's':
			rotation = 270;
			break;
		default:
			break;
	}

    return rotation;
}

bool checkForCorrectInput(const std::string& input, char delimiter, Vector2& output)
{
    std::string widthInput = "";
    std::string heightInput = "";

    int widthOrHeight = 0;

    //By creating a variable, we do not have to check the size of the string every iteration of the loop
    int sizeOfString = input.size();
    for (auto it = input.begin(); it != input.end(); ++it)
    {
        //Delimiter is used to divide up the numbers to two seperate
        if (*it == delimiter)
            widthOrHeight++;
        
        else if (IsNumber(*it))
        {
            //wdithOrHeight keeps track of which number we are adding to
            if (widthOrHeight == 0)
                widthInput += *it;
            else
                heightInput += *it;
        }
        else
        {
            //In case we see invalid characters such as j, we send an error message
            std::cout << "Invalid input: [" << input << "]\n Expected two nubers\n";
            return false;
        }
    }

    if (widthInput.size() < 1 || heightInput.size() < 1)
    {
        std::cout << "Invalid output\n";
        return false;
    }

    //If the user types 001, it will be counted as 1
    int xValue = std::stoi(widthInput);
    int yValue = std::stoi(heightInput);

    //Checks whether one of the numbers are 0
    if (xValue < 1 || yValue < 1)
    {
        std::cout << "Value can not be smaller than 1, you input [" << xValue << "x" << yValue << "] try again\n";
        return false;
    }

    output.x = xValue;
    output.y = yValue;

    return true;
}

namespace InputHandler
{

    void HandleRoombaInputs(RoombaData& rbData)
    {

        //Now we start taking inputs from the user
        InputHandler::HandleSizeAndPositionInput("Enter the size of your room in meters, fill in by typing for example 8x4\n", rbData.roomSize);
    
        //Start position also need to be checked whether it is inside the room
        bool validStartposition = false;
        while (!validStartposition)
        {
            InputHandler::HandleSizeAndPositionInput("Enter the start position of your roomba, fill in by typing for example 4x2\n", rbData.startPosition);
            validStartposition = positionIsValid(rbData.startPosition, rbData.roomSize);
        }

        InputHandler::HandleDirectionInput("Enter the starting direction of your roomba, fill in by typing w, e, s or n\n", rbData.startRotation);
        InputHandler::HandleCommandsInput("Enter the commands your roomba, fill in by typing a string containing w, d, s or a\n", rbData.commands);

    }

    void HandleSizeAndPositionInput(const std::string& infoText, Vector2& output)
    {
        std::string input;

        bool outputCreated = false;
        //We keep giving the user the prompt until they write a correct input
        while (!outputCreated)
        {
            std::cout << infoText;
            std::getline(std::cin, input);

            //If the input is correct and we are able to create an output, end the while loop
            outputCreated = checkForCorrectInput(input, 'x', output);
        }
    }

    void HandleDirectionInput(const std::string& infoText, int& rotation)
    {
        std::string input;

        bool correctString = false;
        //We keep giving the user the prompt until they write a correct input
        while (!correctString)
        {
            std::cout << infoText;
            std::getline(std::cin, input);
            //The input must be one of the follwing
            if (input == "w" || input == "e" || input == "s" || input == "n")
                correctString = true;
            else
                std::cout << "Invalid input: [" << input << "]\n Expected either w, e, s or n\n";
        }

        rotation = convertCharToRotation(input[0]);
    }

    void HandleCommandsInput(const std::string& infoText, std::vector<Commands>& commands)
    {
        std::string input;

        bool correctString = false;
        while (!correctString)
        {
            correctString = true;

            std::cout << infoText;
            std::getline(std::cin, input);

            for (auto it = input.begin(); it != input.end(); ++it)
            {
                //If one of the characters are wrong, the user must try again
                if (*it != 'w' && *it != 'd' && *it != 's' && *it != 'a')
                {
                    std::cout << "Invalid input: [" << *it << "]\n Expected either w, d, s or a\n";
                    correctString = false;
                }
            }
        }

        for (auto it = input.begin(); it != input.end(); ++it) {
            commands.emplace_back(convertCharToCommand(*it));
        }
    }
}

