//------------------------------------------------------------------------
// Bullet.h
//
// Inherites Entity. Manages all the variables needed for fired bullets
//------------------------------------------------------------------------
#pragma once

#include "Entity.h"

class Bullet : public Entity{

private:
	float xVelocity;
	float yVelocity;

public:
	Bullet() {
		entity = App::CreateSprite(ENEMY_SPRITES, 4, 12);
		entity->SetFrame(2);
		entity->SetScale(0.5f);
		xVelocity = 0.0f;
		yVelocity = 0.0f;
	}

	void setPosition(float _xCoordinate, float _yCoordinate);
	void setXVelocity(float _xVelocity);
	void setYVelocity(float _yVelocity);
	float getXVelocity() { return xVelocity; }
	float getYVelocity() { return yVelocity; }
	~Bullet() {

	}
};
