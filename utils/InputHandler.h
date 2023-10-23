#pragma once
#include "Vector2.h"
#include <string>
#include "../roomba/Roomba.h"

namespace InputHandler
{
	//This is the most important function, it sets up the pipeline for inputting the data needed
	void HandleRoombaInputs(RoombaData& rbData);

	void HandleSizeAndPositionInput(const std::string& infoText, Vector2& output);

	void HandleDirectionInput(const std::string& infoText, int& rotation);

	void HandleCommandsInput(const std::string& infoText, std::vector<Commands>& commands);
};