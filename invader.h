#ifndef INVADER_H
#define INVADER_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
//#include <tuple>
#include <unistd.h>

#include "lead.h"
//location , model (from main or transfer) , status (health, dmg, etc.), spawn rate,  
Lead bullet;

class Invader
{
private:
sf::Vector2f setInvPos;
sf::Vector2f invPos;
float xLoc;
float yLoc;


sf::Sprite inv;
//std::vector<sf::Sprite>sprVec;
bool collision;
bool alive;
unsigned mainCounter;
int count;
int type;
int health; // = 100
int hitLanded = 0;
int leadType;
int enemiesOnScreen = 0;
int dmg;

float spd;
const float maxX = 800;
const float maxY = 600;

// void SetVars();
// void Counter();
// void SetTexture();

public: 
//Invader() = default;

//Invader(float px , float py, float spd);
//virtual ~Invader();
Invader()
{
    inv.setPosition(xLoc, yLoc);
}

void SetPos(float x, float y)
{
    x = xLoc;
    y = yLoc;
    
}
float GetPos()
{
    return xLoc, yLoc;
}

void SetType(int invType)
{
    invType = type;
    alive = true;
    enemiesOnScreen+=1;
}

int GetType()
{
    return type;
}

void TypeSpawn()
{
    if(enemiesOnScreen <= 3)
    {
    //get texture / push
    //sprVec.push_back(this->inv);
    }
}

void SetDamageReport(int lead)
{
    if(bullet.bulletPostion.x == xLoc || bullet.bulletPostion.y == yLoc)
    {
        hitLanded +=1;
    //leadType = lead;
    
    switch(lead){
    case 1:
        if(type = 1)
        {
            dmg = -25;
        }
        if(type = 2)
        {
            dmg = -20;
        }
        if(type = 3)
        {
            dmg = -10;
        }
        break;
    case 2:
        if(type = 1)
        {
            dmg = -30;
        }
        if(type = 2)
        {
            dmg = -25;
        }
        if(type = 3)
        {
            dmg = -15;
        }
    break;
    case 3:
        if(type = 1)
        {
            dmg = -60;
        }
        if(type = 2)
        {
            dmg = -60;
        }
        if(type = 3)
        {
            dmg = -35;
        }
    break;
    }
    }
}
int GetDmgReport()
{
    return dmg, hitLanded;
}

void CheckDmg()
{
    if(hitLanded == 0)
    {
        dmg = 0;
        health = 100;
        alive = true;
    }
    if(hitLanded > 0)
    {
        health = health + dmg;
    }
    if(health <= 0)
    {
        alive = false;
    }
}

// void Delete()
// {
//     for(std::vector<sf::Sprite>::iterator spr = sprVec.begin(); spr != sprVec.end(); spr++){
//     if(alive == false)
//     {
//         spr = sprVec.erase(spr);
//     }
//     }
// }

void Draw(sf::RenderWindow &window)
{
    window.draw(this->inv);
}


const sf::FloatRect InvBox() const;


// const int& PointCount() const;
// const int& DmgTaken() const;

void UpdateInv();
void RenderInv(sf::RenderTarget* rt);

float px;
float py;


};



// void Rand()
// {
//     randEnemy = 1 + (rand() % 3);
//     //std::cout << randEnemy;
//     //Invader(randEnemy);
// }

// void CheckTime(int totalEnemies) // quantity
// {
//     if(totalEnemies = 0)
//     {
//         sleep(5);
//         Rand();
//     }
//     if(totalEnemies > 0 && totalEnemies <= 3)
//     {
//         sleep(10);
//         Rand();
//     }
//     if(totalEnemies == 3)
//     {
//         sleep(10);
//     }
// }

// void InvPos(sf::Sprite invade)
// {
//     invade.getPosition() == invPos;
// }

// void Hit(sf::Vector2f pos)
// {
//     if(l.bulletPostion == invPos)
//     {
//         collision = true;
//         hitLanded+=1;
//     }
//     if(health <= 0)
//     {
//         enemiesOnScreen-=1;
//     }
// }

// void Dmg(int slugType)
// {
//     switch (slugType)
//     {
//         case 0:
//         slugType = 1;
//         if(enemyType = 1)
//         {
//             health - 25;
//         }
//          if(enemyType = 2)
//         {
//             health - 20;
//         }
//          if(enemyType = 1)
//         {
//             health - 10;
//         }
//         break;
//          case 1:
//         slugType = 2;
//         if(enemyType = 1)
//         {
//             health - 35;
//         }
//          if(enemyType = 2)
//         {
//             health - 30;
//         }
//          if(enemyType = 1)
//         {
//             health - 20;
//         }
//         break;
//          case 2:
//         slugType = 3;
//         if(enemyType = 1)
//         {
//             health - 50;
//         }
//          if(enemyType = 2)
//         {
//             health - 45;
//         }
//          if(enemyType = 1)
//         {
//             health - 35;
//         }
//         break;

//     }
// }


// void SetPos(float x , float y)
// {
//     maxX = x;
//     minX = -x;
//     maxY = y;
//     minY = y;


//     setInvPos.x = x+10;
//     setInvPos.y = y;
// }

// void Move()
// {
//     if(invPos.x <= maxX && invPos.y <= maxY){
//     //invader.move() //randX randY
//     }
// }


// void FireShot()
// {

// }

// void Sights(float xPlain , float yPlain)
// {
//     if(xPlain == invPos.x || yPlain == invPos.y)
//     {
//         FireShot();
//     }
// }

// void DrawInv(sf::RenderWindow &window)
// {
//     window.draw(invader);
// }
// //if plyr sf::Vector2f = collision

// private:

// int dmg;
// int spawnRate;
// sf::Sprite invader;



#endif