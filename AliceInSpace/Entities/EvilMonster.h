//------------------------------------------------------------------------
// EvilMonster.h
//
// Evil Monsters have two lives
//------------------------------------------------------------------------
#pragma once

#include "Entity.h"

class EvilMonster : public Entity {

public:
	EvilMonster() {
		entity = App::CreateSprite(ENEMY_SPRITES, 2, 12);
		lives = 2;
		xCoordinate = rand() % WIDTH + 1.0f;
		yCoordinate = rand() % HEIGHT + 1.0f;
		entity->SetPosition(xCoordinate, yCoordinate);
		entity->SetFrame(2);
		entity->SetScale(0.5f);
		type = MON_EVIL;
	}

	void updatePosition();

	~EvilMonster() {
		
	};
};
