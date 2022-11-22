#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SFML/Window.hpp>
class Controller
{
public:

Controller(const sf::Vector2f& currPos): currPos(currPos){
    moving[(int)RenderIdx::GoRight] = View(64,192,64,64,8,0.1f);
    moving[(int)RenderIdx::GoLeft] = View(64,64,64,64,8,0.1f);
    moving[(int)RenderIdx::Crouch] = View();
    moving[(int)RenderIdx::Crawl] = View();

    moving[(int)RenderIdx::IdleRight] = View(0,192,64,64,1,10.1f);
    moving[(int)RenderIdx::IdleLeft] = View(0,64,64,64,1,10.1f);
                                        //view class
};

void init();
float capControls();
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
sf::Event evt;
    //View class

  
    

};



#endif