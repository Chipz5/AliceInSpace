//------------------------------------------------------------------------
// Entity.cpp
//
// Implements methods common to all entities like screen wrapping, getting/
// setting positions, lives
//------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------
#include "Entity.h"

void Entity::screenWrap() {
	if (xCoordinate > WIDTH) {
		xCoordinate = 0.0f;
	}
	if (xCoordinate < BASE) {
		xCoordinate = WIDTH;
	}
	if (yCoordinate > HEIGHT) {
		yCoordinate = 0.0f;
	}
	if (yCoordinate < BASE) {
		yCoordinate = HEIGHT;
	}
}

void Entity::getPosition(float _xCoordinate, float _yCoordinate) {
	entity->GetPosition(xCoordinate, yCoordinate);
}

void Entity::setPosition() {
	entity->SetPosition(xCoordinate, yCoordinate);
}

void Entity::updatePosition() {
	entity->GetPosition(xCoordinate, yCoordinate);
	screenWrap();
	xCoordinate += rand() % 10 + 1.0f;
	yCoordinate += rand() % 10 + 1.0f;
	entity->SetPosition(xCoordinate, yCoordinate);
}

void Entity::setLives(uint16_t _lives) {
	lives = _lives;
}

void Entity::updateLives() {
	--lives;
}