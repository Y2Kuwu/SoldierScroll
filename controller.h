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

private:
    enum class RenderIdx{
    GoRight,
    GoLeft,
    Crouch,
    Crawl,
    Count 

};


bool gameIsStarted;
sf::Vector2f currPos;
sf::Vector2f velocity;
sf::Sprite spr;
View moving[int( RenderIdx::Count )];
    //View class

  
    

};



#endif