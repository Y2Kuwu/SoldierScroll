#include "controller.h"
#include "tex.h"

Controller::Controller(const sf::Vector2f& currPos): currPos(currPos){
    moving[(int)RenderIdx::GoRight] = Controller(1,1,1,1,1,1)
}

void Controller::init(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && gameIsStarted == true)
{
    gameIsStarted == false;
    //Tex::loadActor(1);
    //Tex::loadPassive();
}
}
void Controller::capControls(){




}



