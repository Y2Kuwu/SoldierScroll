#include "controller.h"
#include "tex.h"

Controller::Controller(){

}

void Controller::init(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && gameIsStarted == true)
{
    gameIsStarted == false;
    //Tex::loadActor(1);
    //Tex::loadPassive(1);
}
}
void Controller::capControls(){




}