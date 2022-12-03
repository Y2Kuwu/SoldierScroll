#ifndef LEAD_H
#define LEAD_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Lead
{
private:
sf::RectangleShape bullet;
sf::Vector2f direction;
float bulletSpeed;

public:
    Lead();
    Lead(sf::RectangleShape* bull, float bullet_speed, float dirX, float dirY, float posX, float posY);
    virtual ~Lead();

    const sf::FloatRect impact() const;
    void UpdateBullet();
    void Render(sf::RenderTarget* rt);
};


 #endif