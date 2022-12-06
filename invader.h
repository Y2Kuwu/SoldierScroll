#ifndef INVADER_H
#define INVADER_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <tuple>
#include "lead.h"
//location , model (from main or transfer) , status (health, dmg, etc.), spawn rate,  
Lead l;


class Invader
{
public:

sf::Vector2f setInvPos;
sf::Vector2f invPos;
std::unordered_map <int, int, std::string, int> Enemy;
bool collision;
bool alive;
int health; // = 100
int hitLanded = 0;
int leadType;
int enemyType;

float maxX;
float maxY;
float minX;
float minY;

Invader() = default;
Invader(int type)
{                                       //slides
    Enemy[type=1] = health,"Light",20; //0-11
    Enemy[type=2] = health,"Med",25; //12-23
    Enemy[type=3] = health,"Heavy",35; // 14-26
}

void InvPos(sf::Sprite invade)
{
    invade.getPosition() == invPos;
}

void Hit(sf::Vector2f pos)
{
    if(l.bulletPostion == invPos)
    {
        collision = true;
        hitLanded+=1;
    }
}

void Dmg(int slugType)
{
    switch (slugType)
    {
        case 0:
        slugType = 1;
        if(enemyType = 1)
        {
            health - 25;
        }
         if(enemyType = 2)
        {
            health - 20;
        }
         if(enemyType = 1)
        {
            health - 10;
        }
        break;
         case 1:
        slugType = 2;
        if(enemyType = 1)
        {
            health - 35;
        }
         if(enemyType = 2)
        {
            health - 30;
        }
         if(enemyType = 1)
        {
            health - 20;
        }
        break;
         case 2:
        slugType = 3;
        if(enemyType = 1)
        {
            health - 50;
        }
         if(enemyType = 2)
        {
            health - 45;
        }
         if(enemyType = 1)
        {
            health - 35;
        }
        break;

    }
}
void EnemyCount(int totEnemies)
{
    if(totEnemies <= 3)
    {
        //push_back new
        //draw
    }
    else
    {
        //wait
    }
}


void SetPos(float x , float y)
{
    maxX = x;
    minX = -x;
    maxY = y;
    minY = y;


    setInvPos.x = x+10;
    setInvPos.y = y;
}

void Move()
{
    if(invPos.x <= maxX && invPos.y <= maxY){
    //invader.move() //randX randY
    }
}


void FireShot()
{

}

void Sights(float xPlain , float yPlain)
{
    if(xPlain == invPos.x || yPlain == invPos.y)
    {
        FireShot();
    }
}

void DrawInv(sf::RenderWindow &window)
{
    window.draw(invader);
}
//if plyr sf::Vector2f = collision

private:
int health;
int dmg;
int spawnRate;
sf::Sprite invader;



};

#endif