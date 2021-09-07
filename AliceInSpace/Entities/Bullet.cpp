//------------------------------------------------------------------------
// Bullet.cpp
// 
// Velocity of the fired bullets are set 
//------------------------------------------------------------------------

#include "stdafx.h"
//------------------------
#include "app\app.h"
//------------------------
#include "Bullet.h"


void Bullet::setPosition(float _xCoordinate, float _yCoordinate) {
	entity->SetPosition(_xCoordinate, _yCoordinate);
}

void Bullet::setXVelocity(float _xVelocity) {
	xVelocity = _xVelocity;
}
void Bullet::setYVelocity(float _yVelocity) {
	yVelocity = _yVelocity;
}