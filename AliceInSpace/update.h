//------------------------------------------------------------------------
// Update.h
//------------------------------------------------------------------------

#pragma once
//-----------------------------
#include <stdlib.h>
#include <iostream>
#include <memory>
//-----------------------------
#include "stdafx.h"
//-----------------------------
#include "App/app.h"
//-----------------------------
#include "Entities\Collectibles.h"
#include "Entities\Player.h"
#include "Entities\GrowMonster.h"
#include "Entities\ShrinkMonster.h"
#include "Entities\EvilMonster.h"


extern std::vector<std::unique_ptr<Collectibles>> collectibles;
extern std::vector<std::unique_ptr<Entity>> monsters;

void spawnCollectibles();
void updateMonsterPosition(float deltaTime);
void updatePlayerPosition(Player* player);
void updateBulletPosition(Player* player, float deltaTime);
void updateCollectibles(float deltaTime);
void detectCollision( Player* player);
bool isLoseConditionSatisfied(Player* player);
void spawnMonsters();
