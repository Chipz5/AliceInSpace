//------------------------------------------------------------------------
// Player.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//-----------------
#include "app\app.h"
//-----------------
#include "Player.h"

void Player::updatePosition(float _xCoordinate,float _yCoordinate) {
	entity->GetPosition(xCoordinate, yCoordinate);
	screenWrap();
	xCoordinate += _xCoordinate;
	yCoordinate += _yCoordinate;
	entity->SetPosition(xCoordinate, yCoordinate);
}

void Player::fireBullets() {
	if (noOfBullets != 0) {
		auto firedBullet = std::make_unique<Bullet>();
		entity->GetPosition(xCoordinate, yCoordinate);
		firedBullet->setPosition(xCoordinate, yCoordinate);
		--noOfBullets;
		if (playerDirection == ANIM_FORWARDS) {
			firedBullet->setYVelocity(10.0f);
		}
		else if (playerDirection == ANIM_BACKWARDS) {
			firedBullet->setYVelocity(-10.0f);
		}
		else if (playerDirection == ANIM_LEFT) {
			firedBullet->setXVelocity(-10.0f);
		}
		else if (playerDirection == ANIM_RIGHT) {
			firedBullet->setXVelocity(10.0f);
		}
		bullets.push_back(std::move(firedBullet));
	}

}

void Player::setNoOfBullets(uint16_t _numberOfBullets) {
	noOfBullets += _numberOfBullets;
}

void Player::setPlayerDirection(uint8_t _playerDirection) {
	playerDirection = _playerDirection;
}
