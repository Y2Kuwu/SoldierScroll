#include "controller.h"
#include "tex.h"



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

//   void Controller::timingBelt( float delta )
//     {
//         currPos += velocity * delta;
//         moving[int (currView)].timingBelt( delta );
//         moving[int (currView)].makeSprite( spr );
//     }

void Controller::dir(sf::Vector2f& dirXY){
    if( dirXY.x > 0.0f && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        
    }

    

    
    
    }    
    
