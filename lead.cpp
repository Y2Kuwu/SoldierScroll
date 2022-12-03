#include "lead.h"
#include "SFML/Graphics.hpp"
Lead::Lead(){}

float bulletSpeed;

    Lead::Lead(sf::RectangleShape* bull, float bullet_speed, float dirX, float dirY, float posX, float posY)
    {
        //this->bullet.setTexture(*bull);
        this->bullet.setPosition(posX,posY);
        this->direction.x = posX;
        this->direction.y = posY;
        this->bulletSpeed = bullet_speed;
    }
    
    Lead::~Lead(){}

    const sf::FloatRect Lead::impact() const
{
	return this->bullet.getGlobalBounds();
}

void Lead::UpdateBullet()
{
	//Movement
	this->bullet.move(this->bulletSpeed * this->direction);
}

void Lead::Render(sf::RenderTarget * rt)
{
	rt->draw(this->bullet);
}