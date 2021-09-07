//------------------------------------------------------------------------
// ShrinkMonster.h
//
// Shrink Monsters only have one life
//------------------------------------------------------------------------
#pragma once

#include "Entity.h"

class ShrinkMonster : public Entity {

public:
	ShrinkMonster() {
		entity = App::CreateSprite(ENEMY_SPRITES, 3, 12);
		lives = 1;
		xCoordinate = rand() % WIDTH + 1.0f;
		yCoordinate = rand() % HEIGHT + 1.0f;
		entity->SetPosition(xCoordinate, yCoordinate);
		entity->SetFrame(2);
		entity->SetScale(0.5f);
		type = MON_SHRINK;
	}

	void updatePosition();
	~ShrinkMonster() {
		
	}
};