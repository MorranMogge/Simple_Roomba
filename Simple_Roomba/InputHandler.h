#pragma once
#include "Vector2.h"
#include <string>

namespace InputHandler
{
	bool checkForCorrectInput(const std::string& input, char delimiter, Vector2& output);

	void HandleSizeAndPositionInput(std::string infoText, std::string& input, Vector2& output);

	void HandleDirectionInput(std::string infoText, std::string& input);

	void HandleCommandsInput(std::string infoText, std::string& input);
};