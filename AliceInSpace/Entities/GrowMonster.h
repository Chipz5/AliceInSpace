//------------------------------------------------------------------------
// GrowMonster.h
// 
// Grow Monsters have only one life
//------------------------------------------------------------------------
#pragma once

#include "Entity.h"

class GrowMonster : public Entity {

public:
	GrowMonster() {
		entity = App::CreateSprite(ENEMY_SPRITES, 10, 12);
		lives = 1;
		xCoordinate = rand() % WIDTH + 1.0f;
		yCoordinate = rand() % HEIGHT + 1.0f;
		entity->SetPosition(xCoordinate, yCoordinate);
		entity->SetFrame(2);
		entity->SetScale(0.5f);
		type = MON_GROW;
	}

	void updatePosition();
	~GrowMonster() {
		
	};
};