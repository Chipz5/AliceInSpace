//------------------------------------------------------------------------
// Game.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "update.h"
#include "GameStateManager.h"
//------------------------------------------------------------------------

Player* player;

void Init() {
    spawnMonsters();
    player = new Player();
}

void Update(float deltaTime)
{
    if (hasGameStarted && !isGameLost) {

        spawnCollectibles();

        spawnMonsters();

        updateMonsterPosition(deltaTime);
        
        player->getEntity()->Update(deltaTime);
        updatePlayerPosition(player);
        if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
        {
            player->fireBullets();
        }

        updateBulletPosition(player, deltaTime);

        updateCollectibles(deltaTime);

        detectCollision(player);

        isGameLost = isLoseConditionSatisfied(player);

        t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        if (time_span.count() >= 200) {
            isGameWon = true;
            isGameLost = false;
        }
       
        
    }
    else {
        if (App::GetController().GetLeftThumbStickY() < -0.5f) {
            hasGameStarted = true;
            t1 = high_resolution_clock::now();
        }
     }

    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP))
    {
        App::PlaySound(".\\Media\\bg.wav", true);
    }
    

}

void displayMainScreen() {
    App::Print(250, 600, "------------- ALICE IN SPACE ----------------", 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(150, 500, "Alice has fallen down a rabbit hole... yet again! But this time she's found herself in a void", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(150, 470, "Help her survive the void till the timer hits 200... but beware of the monsters that lurk around!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(100, 450, "Just like the potions in Wonderland, some monsters will shrink her, some will make her grow... ", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(250, 430, "and the others will kill her. But don't worry, she's equipped with a firearm.", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(230, 410, "She can also collect special items which will either increase her life or the bullet count.", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(250, 390, "But don't wait too long as these items will disappear after a while", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(200, 370, "P.S : Make sure she doesn't get too big or shrink too small or she dies instantly.", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    App::Print(300, 200, "Controls : W,A,S,D to move , Spacebar to shoot", 1.0f, 0.0f, 1.0f);
    App::Print(390, 300, "Press W to start the game", 1.0f, 1.0f, 0.0f);
}


void Render()
{

    if (isGameLost) {
        App::Print(350, 500, "Oh no! Alice is Stuck in space forever! :(");
    }
    else if (isGameWon){

        App::Print(250, 500, "Yay! You helped Alice escape. Let's hope she doesn't fall into another rabbit hole :)");
    }
    else if (hasGameStarted) {
        
        for (int i = 0; i < player->bullets.size(); i++) {
            player->bullets[i]->getEntity()->Draw();

        }
        player->getEntity()->Draw();

        for (int i = 0; i < monsters.size(); ++i) {
            monsters[i]->getEntity()->Draw();
        }

        for (int i = 0; i < collectibles.size(); ++i) {
            collectibles[i]->getEntity()->Draw();
        }
        uint16_t lives = player->getLives();
        uint16_t bullets = player->getNoOfBullets();
        t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::string livesDisplay = "Lives: " + std::to_string(lives);
        std::string bulletsDisplay = "Bullets: " + std::to_string(bullets);
        std::string timerDisplay = "Timer: " + std::to_string(time_span.count());
        App::Print(100, 600, livesDisplay.c_str(), 1.0f, 1.0f, 0.0f);
        App::Print(800, 600, bulletsDisplay.c_str(), 1.0f, 1.0f, 0.0f);
        App::Print(450, 600, timerDisplay.c_str(), 1.0f, 1.0f, 0.0f);

    }
    else {
        displayMainScreen();
    }
}

void Shutdown()
{
    if (player) {
        if (player->bullets.size() > 0) {
            player->bullets.clear();
        }
        delete player;
    }
    
    monsters.clear();
    collectibles.clear();
}
