//------------------------------------------------------------------------
// Update.cpp
//------------------------------------------------------------------------

#include "stdafx.h"
//------------------------
#include "update.h"

std::vector<std::unique_ptr<Collectibles>> collectibles;
std::vector<std::unique_ptr<Entity>> monsters;

/*
* Spawn Collectibles
* 
* Checks whether collectibles can be spawned. At a time only 2 collectibles can be 
* active. 
* 
*/
void spawnCollectibles() {
    bool canSpawnCollectible = (rand() % 500 == 0);
    if (collectibles.size() < 2 && canSpawnCollectible) {
        auto collect = std::make_unique<Collectibles>();
        collectibles.push_back(std::move(collect));
    }
}

/*
*  Update Monster Position. Each type of monster moves in different speed and direction. 
* Supports screen wrapping
*/
void updateMonsterPosition(float deltaTime) {
    for (int i = 0; i < monsters.size(); ++i) {
        monsters[i]->getEntity()->Update(deltaTime);
        monsters[i]->updatePosition();
    }
}

/*
*  Updates the player position. Supports screen wrapping.
*/
void updatePlayerPosition(Player* player) {
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        player->getEntity()->SetAnimation(ANIM_RIGHT);
        player->updatePosition(3.0f, 0.0f);
        player->setPlayerDirection(ANIM_RIGHT);
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        player->getEntity()->SetAnimation(ANIM_LEFT);
        player->updatePosition(-3.0f, 0.0f);
        player->setPlayerDirection(ANIM_LEFT);
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        player->getEntity()->SetAnimation(ANIM_BACKWARDS);
        player->updatePosition(0.0f, -3.0f);
        player->setPlayerDirection(ANIM_BACKWARDS);
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        player->getEntity()->SetAnimation(ANIM_FORWARDS);
        player->updatePosition(0.0f, 3.0f);
        player->setPlayerDirection(ANIM_FORWARDS);
    }
}

/*
*  Updates the bullet position. Bullet gets destroyed when it leaves the frame.
*/

void updateBulletPosition(Player* player, float deltaTime) {
    for (int i = 0; i < player->bullets.size(); i++) {
        player->bullets[i]->getEntity()->Update(deltaTime);
        float x, y;
        player->bullets[i]->getEntity()->GetPosition(x, y);
        x += player->bullets[i]->getXVelocity();
        y += player->bullets[i]->getYVelocity();
        player->bullets[i]->getEntity()->SetPosition(x, y);
        if (x > WIDTH || x < BASE || y > HEIGHT || y < BASE) {
            player->bullets.erase(player->bullets.begin() + i);
        }
    }
}


/*
* Updates the collectible lifespan
*/
void updateCollectibles(float deltaTime) {
    for (int i = 0; i < collectibles.size(); i++) {
        collectibles[i]->getEntity()->Update(deltaTime);
        if (collectibles[i]->getLives() <= 0) {
            collectibles.erase(collectibles.begin() + i);
        }
        else {
            collectibles[i]->updateLifespan();
        }
    }
}

bool inline inRange(float low, float high, float x)
{
    return  (x >= low && x <= high);
}

/*
*  Player - Monster collision
* 
*  If player collides with the evil Monster, player loses a life.
*  If the player collides with the shrink Monster, they shrink by 1 size
*  and they grow by 1 size if they collide with a grow monster.
*  In all cases, the Monster is destroyed on collision.
* 
*/
void playerMonsterCollisionDetected(Player* player, int i) {
    if (monsters[i]->getType() == MON_GROW) {
        float playerSize = player->getEntity()->GetScale();
        player->getEntity()->SetScale(playerSize + 1);
        monsters.erase(monsters.begin() + i);
        return;
    }
    else if (monsters[i]->getType() == MON_SHRINK) {
        float playerSize = player->getEntity()->GetScale();
        player->getEntity()->SetScale(playerSize - 1);
        monsters.erase(monsters.begin() + i);
        return;
    }
    else if (monsters[i]->getType() == MON_EVIL) {
        uint16_t playerLives = player->getLives();
        player->setLives(playerLives - 1);
        monsters.erase(monsters.begin() + i);
        return;
    }
}

/*
*  Player - Collectible collision
*
*  If player collides with a collectible, they will gain a life if the collectible 
* is a life type or they can gain 20 bullets if the collectible type is bullet.
*
*/

void detectCollectiblePlayerCollision(Player* player) {
    float xPlayer, yPlayer;
    player->getEntity()->GetPosition(xPlayer, yPlayer);
    float xPlayerLowRange = xPlayer - (player->getEntity()->GetWidth() / 10) * player->getScale();
    float xPlayerUpRange = xPlayer + (player->getEntity()->GetWidth() / 10) * player->getScale();
    float yPlayerLowRange = yPlayer - (player->getEntity()->GetHeight() / 10) * player->getScale();
    float yPlayerUpRange = yPlayer + (player->getEntity()->GetHeight() / 10) * player->getScale();

    for (int i = 0; i < collectibles.size(); i++) {
        float x, y;
        collectibles[i]->getEntity()->GetPosition(x, y);
        float xLowRange = x - collectibles[i]->getEntity()->GetWidth() / 5;
        float xUpRange = x + collectibles[i]->getEntity()->GetWidth() / 5;
        float yLowRange = y - collectibles[i]->getEntity()->GetHeight() / 5;
        float yUpRange = y + collectibles[i]->getEntity()->GetHeight() / 5;
        

        if ((inRange(xLowRange, xUpRange, xPlayerLowRange) || inRange(xLowRange, xUpRange, xPlayerUpRange))
            && (inRange(yLowRange, yUpRange, yPlayerLowRange) || inRange(yLowRange, yUpRange, yPlayerUpRange))) {
            if (collectibles[i]->getType() == BULLETS) {
                player->setNoOfBullets(20);
            }
            else if (collectibles[i]->getType() == LIFE) {
                player->setLives(player->getLives() + 1);
            }
            collectibles.erase(collectibles.begin() + i);
            App::PlaySound(".\\Media\\collect.wav");

        }

    }
}

/*
*  Checks collision between objects in the game. This is done by creating a small collision box space.
*  When two collision spaces of objects overlap, collsion is detected.
* 
*  If monsters collide with the player, they are destroyed immediately, but if they collide with the bullet,
*  they lose a life.
*/
void detectCollision( Player* player) {
    float xPlayer, yPlayer;
    player->getEntity()->GetPosition(xPlayer, yPlayer);
    float xPlayerLowRange = xPlayer - (player->getEntity()->GetWidth() / 10) * player->getScale();
    float xPlayerUpRange = xPlayer + (player->getEntity()->GetWidth() / 10) * player->getScale();
    float yPlayerLowRange = yPlayer - (player->getEntity()->GetHeight() / 10) * player->getScale();
    float yPlayerUpRange = yPlayer + (player->getEntity()->GetHeight() / 10) * player->getScale();

    for (int i = 0; i < monsters.size(); i++) {
        float xMonster, yMonster;
        monsters[i]->getEntity()->GetPosition(xMonster, yMonster);
        float xLowRange = xMonster - monsters[i]->getEntity()->GetWidth()/10;
        float xUpRange = xMonster + monsters[i]->getEntity()->GetWidth()/10;
        float yLowRange = yMonster - monsters[i]->getEntity()->GetHeight()/10;
        float yUpRange = yMonster + monsters[i]->getEntity()->GetHeight()/10;
        
        if ((inRange(xLowRange, xUpRange, xPlayerLowRange) || inRange(xLowRange, xUpRange, xPlayerUpRange))
            && (inRange(yLowRange, yUpRange, yPlayerLowRange) || inRange(yLowRange, yUpRange, yPlayerUpRange))) {
            
            playerMonsterCollisionDetected(player, i);

        }

        for (int j = 0; j < player->bullets.size(); j++) {
            float xBullet, yBullet;
            player->bullets[j]->getEntity()->GetPosition(xBullet, yBullet);
            float xBulletLowRange = xBullet - player->bullets[j]->getEntity()->GetWidth() / 10;
            float xBulletUpRange = xBullet + player->bullets[j]->getEntity()->GetWidth() / 10;
            float yBulletLowRange = yBullet - player->bullets[j]->getEntity()->GetHeight() / 10;
            float yBulletUpRange = yBullet + player->bullets[j]->getEntity()->GetHeight() / 10;
           
            if ((inRange(xLowRange, xUpRange, xBulletLowRange) || inRange(xLowRange, xUpRange, xBulletUpRange))
                && (inRange(yLowRange, yUpRange, yPlayerLowRange) || inRange(yLowRange, yUpRange, yPlayerUpRange))) {
                player->bullets.erase(player->bullets.begin() + j);
                monsters[j].get()->updateLives();
                if (monsters[j].get()->getLives() == 0) {
                    monsters.erase(monsters.begin() + j);
                    App::PlaySound(".\\Media\\Test.wav");
                    return;
                }
            }
            
        }
    }

    detectCollectiblePlayerCollision(player);
    
}

/*
*  Checks for lose condition.
* 
*  Game is lost if the player loses all lives or if the player's size increases beyond 4
*  or decreases beyond 1.
*/
bool isLoseConditionSatisfied(Player* player) {
    if (player->getLives() == 0) {
        return true;
    }
    else if (player->getScale() > 4 || player->getScale() < 1) {
        return true;
    }
    return false;
}

/*
*  Spawns monsters
*/

void spawnMonsters() {
    if (monsters.size() < 5) {
        for (int i = 0; i < rand() % 3; ++i) {
            auto mon = std::make_unique<EvilMonster>();
            monsters.push_back(std::move(mon));
        }
        for (int i = 0; i < rand() % 2; ++i) {
            auto mon = std::make_unique<ShrinkMonster>(); 
            monsters.push_back(std::move(mon));
        }
        for (int i = 0; i < rand() % 3; ++i) {
            auto mon = std::make_unique<GrowMonster>();
            monsters.push_back(std::move(mon));
        }
    }
}