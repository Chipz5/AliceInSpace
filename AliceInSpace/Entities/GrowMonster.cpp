//------------------------------------------------------------------------
// GrowMonster.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//-------------------
#include "app\app.h"
//-------------------
#include "GrowMonster.h"


void GrowMonster::updatePosition() {
	entity->GetPosition(xCoordinate, yCoordinate);
	screenWrap();
	xCoordinate -= rand() % 5 + 1.0f;
	yCoordinate -= rand() % 5 + 1.0f;
	entity->SetPosition(xCoordinate, yCoordinate);
}
