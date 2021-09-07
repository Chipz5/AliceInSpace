//------------------------------------------------------------------------
// ShrinkMonster.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------
#include "app\app.h"
//------------------
#include "ShrinkMonster.h"


void ShrinkMonster::updatePosition() {
	entity->GetPosition(xCoordinate, yCoordinate);
	screenWrap();
	xCoordinate += rand() % 5 + 1.0f;
	yCoordinate += rand() % 10 + 1.0f;
	entity->SetPosition(xCoordinate, yCoordinate);
}
