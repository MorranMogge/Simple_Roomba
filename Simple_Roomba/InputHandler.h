#pragma once
#include "Vector2.h"
#include <string>

namespace InputHandler
{
	bool checkForCorrectInput(const std::string& input, char delimiter, Vector2& output);

	void HandleSizeAndPositionInput(const std::string& infoText, Vector2& output);

	void HandleDirectionInput(const std::string& infoText);

	void HandleCommandsInput(const std::string& infoText, std::string& input);
};