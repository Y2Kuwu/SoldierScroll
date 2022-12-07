#ifndef LEAD_H
#define LEAD_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Lead
{

    public: 
    
    float posX;
    float posY;
    sf::Vector2f bulletPostion; //= lead.getPosition();
    sf::Vector2f trailPosition;
    Lead() = default;
    Lead(sf::Vector2f sz , sf::Vector2f szTrail)
    {
        lead.setSize(sz);
        lead.setOutlineColor(sf::Color::White);
        lead.setOutlineThickness(1);
        lead.setFillColor(sf::Color::Black);
        leadTrail.setSize(szTrail);
        leadTrail.setFillColor(sf::Color::Yellow);
        
    }
    
    void Traj(float speedX , float speedY)
    {
        lead.move(speedX , speedY);
        leadTrail.move(speedX , speedY);
        bulletPostion = lead.getPosition();
        trailPosition = leadTrail.getPosition();
    }

    void PosFire(sf::RenderWindow &window)
    {
        window.draw(lead);
        window.draw(leadTrail);
    }

    void SetPos(sf::Vector2f newPos, sf::Vector2f newOff)
    {
        lead.setPosition(newPos);
        leadTrail.setPosition(newOff);
    }

    private: 
    sf::RectangleShape lead;
    sf::RectangleShape leadTrail;
};


 #endif