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



void Controller::dir(sf::Vector2f& dirXY){
    if( dirXY.x > 0.0f && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        spd = 50.0f;
        act = RenderIdx::GoRight;
    }
    else if( dirXY.x < 0.0f && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        spd = 50.0f;
        act = RenderIdx::GoLeft;
    }
    else if( dirXY.x > 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        spd = 75.0f;
        act = RenderIdx::GoRight;
    }
    else if( dirXY.x < 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        spd = 75.0f;
        act = RenderIdx::GoLeft;
    }
    //add up or jump?
    else{
        if (velocity.x > 0.0f){
            spd = 0.0f;
            act = RenderIdx::IdleRight;
        }
        else if (velocity.x < 0.0f){
            spd = 0.0f;
            act = RenderIdx::IdleLeft;
        }
        velocity = dirXY * spd;
    }
}
    
      void Controller::timingBelt( float delta )
    {
        currPos += velocity * delta;
        moving[int (act)].TimingBelt( delta );
        moving[int (act)].makeSprite( spr );
        spr.setPosition(currPos);
    }

    
    
    }    
    
