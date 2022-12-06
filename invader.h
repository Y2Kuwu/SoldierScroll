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

sf::Vector2f invPos;
std::unordered_map <int, int, std::string, int> Enemy;
bool collision;
int health; // = 100
int hitLanded = 0;
int leadType;
int enemyType;

Invader() = default;
Invader(int type)
{                                       //slides
    Enemy[type=1] = health,"Light",20; //0-11
    Enemy[type=2] = health,"Med",25; //12-23
    Enemy[type=3] = health,"Heavy",35; // 14-26
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

void Sights(float xPlain , float yPlain)
{
    
}
//if plyr sf::Vector2f = collision

private:
int health;
int dmg;
int spawnRate;
sf::Sprite invader



};

#endif