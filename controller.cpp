#include "controller.h"
#include "tex.h"
#include "views.h"


void Controller::init(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && gameIsStarted == true)
{
    gameIsStarted = false;
    //Tex::loadActor(1);
    //Tex::loadPassive();
}
}
void Controller::capControls(){
    sf::Vector2f dirXY = { 0.0f,0.0f };
    switch(evt.type == sf::Event::KeyPressed){
    case sf::Keyboard::Left: //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
        spd = 50.0f;
        dir(dirXY);
    break;
    case sf::Keyboard::Right: //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
        spd = 50.0f;
        dir(dirXY);
    break;

    case sf::Keyboard::A: //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
        spd = 50.0f;
        dir(dirXY);
    break;
    case sf::Keyboard::D: //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
        spd = 50.0f;
        dir(dirXY);
    break;

    case sf::Keyboard::Left + sf::Keyboard::RShift: //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
        spd = 75.0f;
        dir(dirXY);
    break;
    case sf::Keyboard::Right + sf::Keyboard::RShift: //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
        spd = 75.0f;
        dir(dirXY);
    break;

    case sf::Keyboard::A + sf::Keyboard::RShift: //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
        spd = 75.0f;
        dir(dirXY);
    break;
    case sf::Keyboard::D + sf::Keyboard::RShift: //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
        spd = 75.0f;
        dir(dirXY);
    break;

    // case sf::Keyboard::RShift && sf::Keyboard::A || sf::Keyboard::Left:
    //     dirXY.x -= 1.0f;
    //     dir(dirXY);
    // break;
    // case sf::Keyboard::RShift && sf::Keyboard::D || sf::Keyboard::Right:
    //     dirXY.x += 1.0f;
    //     dir(dirXY);
    // break;
    }
    }




void Controller::dir(sf::Vector2f& dirXY){
    if( dirXY.x > 0.0f ){// && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        //spd = 50.0f;
        act = RenderIdx::GoRight;
    }
    else if( dirXY.x < 0.0f ){// && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
       // spd = 50.0f;
        act = RenderIdx::GoLeft;
    }
    // else if( dirXY.x > 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
    //     spd = 75.0f;
    //     act = RenderIdx::GoRight;
    // }
    // else if( dirXY.x < 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
    //     spd = 75.0f;
    //     act = RenderIdx::GoLeft;
    // }
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

    
    
    
    
