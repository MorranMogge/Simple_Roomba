#include "InputHandler.h"
#include <iostream>
#include <array>
#include <algorithm>

bool IsNumber(char character)
{

    //Converts the string to ASCII values, easier to check if they are numbers this way
    int ASCIIvalue = static_cast<int>(character);
    int lowerLimit = static_cast<int>('0');
    int upperLimit = static_cast<int>('9');

    //This also removes the ability to write negative numbers, sinze the ascii code of "-" is not included
    return ASCIIvalue >= lowerLimit && ASCIIvalue <= upperLimit;
}

bool PositionIsValid(Vector2 position, Vector2 roomSize)
{
    //In case it goes out of bounds, we write an error message and return false
    if (position.x < 1 || position.y < 1 ||position.x > roomSize.x || position.y > roomSize.y)
    {
        std::cout << "Invalid position: [" << position.x << "x" << position.y << "]\nRoomba is outside of room (" << roomSize.x << "x" << roomSize.y << ")\n";
        return false;
    }
    return true;
}

Commands ConvertCharToCommand(char character)
{
    Commands cmd = character == 'w' ? Commands::FORWARD : character == 's' ? Commands::BACKWARD :
          character == 'a' ? Commands::LEFT : character == 'd'? Commands::RIGHT : Commands::IDLE;

    return cmd;
}

int ConvertCharToRotation(char character)
{
    int rotation = character == 'e' ? 0 : character == 'n' ? 90 :
        character == 'w' ? 180 : character == 's' ? 270 : 0; 

    return rotation;
}

bool ValidateIfCorrectInput(const std::string& input, char delimiter, Vector2& output)
{
    const int dimensions = 2;
    std::array<std::string, dimensions> widthAndHeight;

    int widthOrHeight = 0;
    //Will keep traversing the string until we are at the last character or if 
    //enough delimiters are seen, will interpret 5x5x5 as 5x5 if we only work in 2D
    for (auto it = input.begin(); it != input.end() && widthOrHeight < (int)widthAndHeight.size(); ++it)
    {
        //Delimiter is used to divide up the numbers to two seperate
        if (*it == delimiter)
            widthOrHeight++;
        //wdithOrHeight keeps track of which number we are adding to
        else if (IsNumber(*it))
            widthAndHeight.at(widthOrHeight) += *it;
        else
        {
            //In case we see invalid characters such as j, we send an error message
            std::cout << "Invalid input: [" << input << "]\n Expected two nubers\n";
            return false;
        }
    }

    if (std::count_if(widthAndHeight.begin(), widthAndHeight.end(), [](std::string str){ return str.size() < 1; }))
    {
        std::cout << "Invalid output\n";
        return false;
    }

    std::vector<int> whValues(dimensions);

    //If the user types 001, it will be interpreted as 1
    auto iterator = widthAndHeight.begin();
    std::generate_n(whValues.begin(), whValues.size(), [&iterator](){ return std::stoi(*(iterator++)); });

    //Checks whether one of the numbers are 0
    if (std::count_if(whValues.begin(), whValues.end(), [](int n){ return n < 1; }))
    {
        //Writes all the numbers the user input
        std::cout << "Value can not be smaller than 1, you input [";
        for (int i = 0; i < (int)widthAndHeight.size(); i++)
        {
            std::string tmp = widthAndHeight.at(i);
            tmp += i != (int)(widthAndHeight.size())-1 ? "x" : "";
            std::cout << tmp;
        }
        std::cout << "] try again\n";
        return false;
    }

    auto it = whValues.begin();
    output.x = *it++;
    output.y = *it;

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
            validStartposition = PositionIsValid(rbData.startPosition, rbData.roomSize);
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
            outputCreated = ValidateIfCorrectInput(input, 'x', output);
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

        rotation = ConvertCharToRotation(input[0]);
    }

    void HandleCommandsInput(const std::string& infoText, std::vector<Commands>& commands)
    {
        std::string input ;

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

        //Converts the recored inputs to commands by converting the chars
        for (auto it = input.begin(); it != input.end(); ++it) {
            commands.emplace_back(ConvertCharToCommand(*it));
        }
    }
}

