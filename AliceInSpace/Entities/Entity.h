//------------------------------------------------------------------------
// Entity.h
//
// Defines all features required by the game entities: enemy, player, etc 
//------------------------------------------------------------------------
#pragma once

#include "stdafx.h"
//------------------------
#include "app\app.h"

#define WIDTH (1000)	
#define HEIGHT (700)	
#define BASE (0.0f)	

enum : uint8_t
{
	MON_EVIL,
	MON_SHRINK,
	MON_GROW,
};

class Entity {

protected:
	const char* PLAYER_SPRITE = ".\\Media\\Test.bmp";
	const char* ENEMY_SPRITES = ".\\Media\\Ships.bmp";
	CSimpleSprite* entity;
	uint16_t lives;
	uint8_t type = 0;
	float xCoordinate = 0 , yCoordinate = 0;


public:

	Entity::Entity() {
		entity = App::CreateSprite(PLAYER_SPRITE, 8, 4);
		lives = 1;
	}
	
	Entity::Entity(CSimpleSprite* _entity) {
		entity = _entity;
		lives = 1;
	}

	virtual void updatePosition();
	void screenWrap();
	void setLives(uint16_t _lives);
	void updateLives();
	void getPosition(float _xCoordinate, float _yCoordinate);
	void setPosition();
	uint16_t getLives() { return lives; }
	uint8_t getType() { return type; }
	CSimpleSprite* getEntity() { return entity; }
	
	virtual ~Entity() {
		delete entity;
	}

};