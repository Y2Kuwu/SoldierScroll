#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SFML/Window.hpp>
class Controller
{
public:

Controller(const sf::Vector2f& currPos): currPos(currPos){
    moving[(int)RenderIdx::GoRight] = View(1,1,1,1,1,1);
                                        //view class
};

void init();
void capControls();
void timingBelt( float delta );
void draw(sf:: RenderTarget& render);
void dir (sf::Vector2f& dirXY);


private:
    enum class RenderIdx{
    GoRight,
    GoLeft,
    Crouch,
    Crawl,

    IdleRight,
    IdleLeft,

    Count 

};


bool gameIsStarted;
float spd; // if shift * 1.5;
sf::Vector2f currPos;
sf::Vector2f velocity = {0.f,0.f};
sf::Sprite spr;
View moving[int( RenderIdx::Count )];
RenderIdx act = RenderIdx::IdleRight;
    //View class

  
    

};



#endif