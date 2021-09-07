//------------------------------------------------------------------------
// GameStateManager.h
// Stores information about state of the game
//------------------------------------------------------------------------
#pragma once
#include <chrono>

bool hasGameStarted = false;
bool isGameLost = false;
bool isGameWon = false;

using namespace std::chrono;
high_resolution_clock::time_point t1;
high_resolution_clock::time_point t2;