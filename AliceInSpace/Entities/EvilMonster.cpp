//------------------------------------------------------------------------
// EvilMonster.cpp
//
//------------------------------------------------------------------------
#include "stdafx.h"
//-------------------
#include "app\app.h"
//--------------------
#include "EvilMonster.h"



void EvilMonster::updatePosition() {
	entity->GetPosition(xCoordinate, yCoordinate);
	screenWrap();
	xCoordinate += rand() % 5 + 1.0f;
	yCoordinate += rand() % 20 + 1.0f;
	entity->SetPosition(xCoordinate, yCoordinate);
}

