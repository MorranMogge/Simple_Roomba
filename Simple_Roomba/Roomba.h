#pragma once
#include "Vector2.h"
#include <vector>

enum Commands
{
	RIGHT,
	LEFT,
	FORWARD,
	BACKWARD
};

//This is all the data that the roomba needs
struct RoombaData
{
	Vector2 roomSize;
	Vector2 startPosition;
	int startRotation;
	std::vector<Commands> commands;
};

class Roomba
{
private:
	Vector2 m_position;
	Vector2 m_direction;
	Vector2 m_roomSize;
	int m_rotation;

	bool outOfBounds();
	void updateRotation();

public:
	Roomba();
	Roomba(const RoombaData& rbData);

	void rotate(int degree);
	bool move(int fwd);
	void printPositionData();

	Vector2 getPosition() const;
	Vector2 getDirection() const;
};