#include "Roomba.h"
#include <math.h>
#include <iostream>

void Roomba::updateRotation()
{
	//Convert degrees to radians
	float radians = (float)m_rotation * M_PI / 180.f;

	//By using this way of calculating the direction, we will be albe to calculate any degree of rotation, we use round() right now since our current interest is only whole numbers
	m_direction = Vector2(round(cos(radians)), round(sin(radians)));

	//Normalize ensures that the length direction vector is always 1, which is important if the app is developed furthur
	m_direction.Normalize();
}

Roomba::Roomba()
	:m_position(Vector2()), m_direction(Vector2()), m_rotation(0)
{
}

Roomba::Roomba(const RoombaData& rbData)
	:m_position(rbData.startPosition.x, rbData.startPosition.y), m_rotation(rbData.startRotation)
{
	updateRotation();

}


void Roomba::rotate(int degree)
{
	m_rotation += degree;
	updateRotation();
}

void Roomba::move(int fwd)
{
	m_position = m_position + Vector2(fwd * m_direction.x, fwd * m_direction.y);
}

void Roomba::printPositionData()
{
	std::cout << "Position: (" << (int)m_position.x << "x" << (int)m_position.y << ") " 
	<< "Direction: (" << (int)m_direction.x << ", " << (int)m_direction.y << ")\n";
}

Vector2 Roomba::getPosition() const
{
	return m_position;
}

Vector2 Roomba::getDirection() const
{
	return m_direction;
}

