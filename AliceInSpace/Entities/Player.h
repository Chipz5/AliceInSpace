//------------------------------------------------------------------------
// Player.h
// Contains all features of the player. The player starts out with 5 lives.
// The lives increase / decrease when the player encounters a collectible /
// monster respectively. The player also stores the fired bullets and keeps a 
// count of the remaining bullets
//------------------------------------------------------------------------
#pragma once
//----------------------
#include <memory>
//----------------------
#include "Entity.h"
#include "Bullet.h"


#define PLAYER_SPAWN_LOCATION (400.0f)

enum : uint8_t
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};

class Player : public Entity {

private:
	uint8_t playerDirection = ANIM_FORWARDS;
	uint16_t noOfBullets = 100;
	
public:
	Player() {
		entity = App::CreateSprite(PLAYER_SPRITE, 8, 4);
		lives = 5;
		float speed = 1.0f / 15.0f;
		entity->SetPosition(PLAYER_SPAWN_LOCATION, PLAYER_SPAWN_LOCATION);
		entity->SetFrame(2);
		entity->SetScale(2.0f);
		entity->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
		entity->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
		entity->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
		entity->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	}
	std::vector<std::unique_ptr<Bullet>> bullets;
	void updatePosition(float _xCoordinate, float _yCoordinate);
	void fireBullets();
	void setNoOfBullets(uint16_t _numberOfBullets);
	void setPlayerDirection(uint8_t _playerDirection);
	float getScale() { return entity->GetScale(); }
	uint16_t getNoOfBullets() { return noOfBullets; }
	uint8_t getPlayerDirection() { return playerDirection; }
	~Player(){
		
	}
};