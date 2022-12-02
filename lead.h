#ifndef LEAD_H
#define LEAD_H
#include <SFML/Graphics.hpp>
class Lead
{
private:
sf::RectangleShape bullet;
sf::Vector2f traject;
float bulletSpeed;

public:
    Lead();
    Lead(sf::RectangleShape * bull, float bullet_speed, float dirX, float dirY, float posX, float posY);
    virtual ~Lead();

    const sf::FloatRect impact() const;
    void UpdateBullet();
    void Rend(sf::RenderTarget* rt);
};


#endif