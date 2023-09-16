#include "InputHandler.h"
#include <iostream>

namespace InputHandler
{
    bool checkForCorrectInput(const std::string& input, char delimiter, Vector2& output)
    {
        std::string widthInput = "";
        std::string heightInput = "";

        int widthOrHeight = 0;

        //By creating a variable, we do not have to check the size of the string every iteration of the loop
        int sizeOfString = input.size();
        for (int i = 0; i < sizeOfString; i++)
        {
            //Delimiter is used to divide up the numbers to two seperate
            if (input[i] == delimiter)
                widthOrHeight++;
            //Converts the string to ASCII values, easier to check if they are numbers this way
            //This also removes the ability to write negative numbers, sinze the ascii code of "-" is not included
            else if ((int)input[i] > 47 && (int)input[i] < 58)
            {
                //wdithOrHeight keeps track of which number we are adding to
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

    void HandleSizeAndPositionInput(const std::string& infoText, std::string& input, Vector2& output)
    {
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

    void HandleDirectionInput(const std::string& infoText, std::string& input)
    {
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
    }

    void HandleCommandsInput(const std::string& infoText, std::string& input)
    {
        bool correctString = false;
        while (!correctString)
        {
            correctString = true;

            std::cout << infoText;
            std::getline(std::cin, input);

            int stringSize = input.size();
            for (int i = 0; i < stringSize && correctString; i++)
            {
                //If one of the characters are wrong, the user must try again
                if (input[i] != 'w' && input[i] != 'd' && input[i] != 's' && input[i] != 'a')
                {
                    std::cout << "Invalid input: [" << input[i] << "]\n Expected either w, d, s or a\n";
                    correctString = false;
                }
            }
        }
    }
}

