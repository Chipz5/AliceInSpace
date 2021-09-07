//------------------------------------------------------------------------
// Collectibles.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//-------------------------
#include "Collectibles.h"

uint8_t Collectibles::getType() {
	return type;
}

void Collectibles::updateLifespan() {
	--lives;
}