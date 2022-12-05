#ifndef LEAD_H
#define LEAD_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Lead
{
// private:
// sf::Sprite bullet;
// sf::Vector2f direction;
// float bulletSpeed;

// public:
//     Lead();
//     Lead(sf::Texture* bull, float bullet_speed, float dirX, float dirY, float posX, float posY);
//     virtual ~Lead();

//     const sf::FloatRect impact() const;
//     void UpdateBullet();
//     void Render(sf::RenderTarget* rt);

    public: 
    
    float posX;
    float posY;
    
   // Lead::Lead(){}

    Lead(sf::Vector2f sz)
    {
        lead.setSize(sz);
    }

    // float IntPos(float wepX , float wepY)
    // {
    //     wepX = posX;
    //     wepY = posY;
    //     return wepX , wepY;
    // }

    void Traj(float speedX , float speedY)
    {
        lead.move(speedX , speedY);
    }

    float PosRight()
    {
        return lead.getPosition().x + lead.getSize().x;
    }
     float PosLeft()
    {
        return lead.getPosition().x;
    }
     float PosUp()
    {
        return lead.getPosition().y;
    }
     float PosDown()
    {
        return lead.getPosition().y + lead.getSize().y;
    }

    void PosFire(sf::RenderWindow &window)
    {
        window.draw(lead);
    }

    void SetPos(sf::Vector2f newPos)
    {
        
        // pX = posX;
        // pY = posY;
        // newPos.x = posX;
        // newPos.y = posY;
        lead.setPosition(newPos);
    }

    private: 
    sf::RectangleShape lead;
};


 #endif