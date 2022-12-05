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
    sf::Vector2f bulletPostion; //= lead.getPosition();
    //posX = lead.getPosition().x;
   // Lead::Lead(){}
    Lead() = default;
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
        bulletPostion = lead.getPosition();
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
    // void Location(float maxX, float maxY, std::vector<Lead>l)
    // {
    //     if(lead.getPosition().x >= maxX || lead.getPosition().x <= -maxX)
    //     {
    //         l.erase(l.begin());
    //     }
    //     if(lead.getPosition().y >= maxY || lead.getPosition().y <= -maxY)
    //     {
    //         l.erase(l.begin());
    //     }
    // }
    void GetPos(float x, float y)
    {

    }

    private: 
    sf::RectangleShape lead;
};


 #endif