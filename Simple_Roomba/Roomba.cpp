#include "Roomba.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265358979323846

void Roomba::updateRotation()
{
	//Convert degrees to radians
	float radians = (float)this->rotation * PI / 180.f;

	//By using this way of calculating the direction, we will be albe to calculate any degree of rotation
	this->direction = Vector2(round(cos(radians)), round(sin(radians)));

	//Normalize ensures that the length direction vector is always 1, which is important if the app is developed furthur
	this->direction.Normalize();
}

Roomba::Roomba()
	:position(Vector2()), direction(Vector2()), rotation(0)
{
}

void Roomba::setPosition(Vector2 newPos)
{
	this->position = newPos;
}

void Roomba::setRotation(char inRotation)
{
	//Set the rotation
	switch (inRotation)
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

	updateRotation();
}

void Roomba::interpretCommand(char command)
{
	//Interpret the command given a char
	switch (command)
	{
		case 'd':
			rotate(-90);
			break;
		case 'a':
			rotate(90);
			break;
		case 'w':
			move(1);
			break;
		case 's':
			move(-1);
			break;
		default:
			break;
	}
}

void Roomba::rotate(int degree)
{
	rotation += degree;
	updateRotation();
}

void Roomba::move(int fwd)
{
	this->position = this->position + Vector2(fwd * this->direction.x, fwd * this->direction.y);
}

Vector2 Roomba::getPosition() const
{
	return this->position;
}

Vector2 Roomba::getDirection() const
{
	return this->direction;
}

