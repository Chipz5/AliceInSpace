//------------------------------------------------------------------------
// Collectibles.h
//
// Inherites Entity. Can be of two types: Bullet or life. If the Bullet is
// collected the player gets 20 extra bullets. If the life is collected the
// player gets an extra life. 
// The lifespan of a collectible is 1600. Once the counter reaches 0, the 
// collectible disappears.
//------------------------------------------------------------------------
#pragma once

#include "app\app.h"
//-----------------------
#include "Entity.h"

enum : uint8_t
{
	BULLETS,
	LIFE,
};

#define SPAWN_WIDTH (800)	
#define SPAWN_HEIGHT (450)

class Collectibles : public Entity {
	protected:
		uint8_t type;
	public:

		Collectibles() {
			entity = App::CreateSprite(ENEMY_SPRITES, 8, 12);
			if (rand() % 5) {
				type = LIFE;
			}
			else {
				type = BULLETS;
			}
			lives = 1600;
			xCoordinate = rand() % SPAWN_WIDTH + 1.0f;
			yCoordinate = rand() % SPAWN_HEIGHT + 1.0f;
			entity->SetPosition(xCoordinate, xCoordinate);
			entity->SetFrame(2);
			entity->SetScale(0.5f);
		}

		uint8_t getType();
		void updateLifespan();
		~Collectibles() {

		}
};