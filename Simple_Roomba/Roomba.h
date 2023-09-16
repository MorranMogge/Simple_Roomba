#pragma once
#include "Vector2.h"

class Roomba
{
private:
	Vector2 position;
	Vector2 direction;
	int rotation;

	void updateRotation();

public:
	Roomba();

	void setPosition(Vector2 newPos);
	void setRotation(char inRotation);

	void interpretCommand(char command);
	void rotate(int degree);
	void move(int fwd);

	Vector2 getPosition() const;
	Vector2 getDirection() const;

};