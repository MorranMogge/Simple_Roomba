#pragma once
#include "Vector2.h"
#include <string>
#include "Roomba.h"

namespace InputHandler
{
	bool checkForCorrectInput(const std::string& input, char delimiter, Vector2& output);

	void HandleRoombaInputs(RoombaData& rbData);

	void HandleSizeAndPositionInput(const std::string& infoText, Vector2& output);

	void HandleDirectionInput(const std::string& infoText, int& rotation);

	void HandleCommandsInput(const std::string& infoText, std::vector<Commands>& commands);
};