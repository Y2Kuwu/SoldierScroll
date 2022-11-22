
//#include "tex.h"
//#include "views.h"
#include <iostream>
#include "views.h"
#include "tex.h"
class Controller
{
public:
Controller() = default;
Controller(const sf::Vector2f& currPos): currPos(currPos){
    moving[(int)RenderIdx::GoRight] = Views(64,192,64,64,8,0.1f);
    moving[(int)RenderIdx::GoLeft] = Views(64,64,64,64,8,0.1f);
   // moving[(int)RenderIdx::Crouch] = View();
   // moving[(int)RenderIdx::Crawl] = View();

    moving[(int)RenderIdx::IdleRight] = Views(0,192,64,64,1,10.1f);
    moving[(int)RenderIdx::IdleLeft] = Views(0,64,64,64,1,10.1f);
                                        //view class
};

//void init();
// void capControls();
// void Timing( float delta );
// void Draw(sf::RenderTarget& render);
// void Dir (sf::Vector2f& dirXY);


void Dir(sf::Vector2f& dirXY){
    if( dirXY.x > 0.0f ){// && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        //spd = 50.0f;
        act = RenderIdx::GoRight;
    }
    else if( dirXY.x < 0.0f ){// && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
       // spd = 50.0f;
        act = RenderIdx::GoLeft;
    }
   
    else{
        if (velocity.x > 0.0f){
            //spd = 0.0f;
            act = RenderIdx::IdleRight;
        }
        else if (velocity.x < 0.0f){
            //spd = 0.0f;
            act = RenderIdx::IdleLeft;
        }
        velocity = dirXY * spd;
    }
}
    
      void Timing( float delta )
    {
        currPos += velocity * delta;
        moving[int (act)].TimingBelt( delta );
        moving[int (act)].makeSprite( spr );
        spr.setPosition(currPos);
    }

    void Draw(sf::RenderTarget& render)
    {
        render.draw(spr);
    }
   
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

float spd = 50.0f; // if shift * 1.5;
sf::Vector2f currPos;
sf::Vector2f velocity = {0.0f,0.0f};
sf::Sprite spr;
Views moving[int( RenderIdx::Count )];
RenderIdx act = RenderIdx::IdleRight;
sf::Event evt;
    //View class

  
    

};



int main(){
    
    //Controller ctrl;

    sf::RenderWindow win( sf::VideoMode( 800,600 ),"SFML window" );

	{
		Controller actor( { 100.0f,100.0f } );
		Controller actorClone( { 100.0f,200.0f } );
	}

    Tex::ErasePrev();

    Controller actor ({ 100.0f,100.0f });

    auto timePtr = std::chrono::steady_clock::now();
    
    while( win.isOpen() )
	{
		// Process events
		sf::Event event;
		while( win.pollEvent( event ) )
		{
			// Close window: exit
			if( event.type == sf::Event::Closed )
				win.close();
		}

    float delta;
    {
        const auto timePtrClone = std::chrono::steady_clock::now();
        delta = std::chrono::duration<float>( timePtrClone - timePtr).count();
        timePtr = timePtrClone;
    }

    //Controller capControls(){
   // event.key.code;
    sf::Vector2f dirXY = { 0.0f,0.0f };
    //switch(event.key.code){
    if (sf::Keyboard::Left){ //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
       // actor.spd = 50.0f;
       // ctrl.Dir(dirXY);
    }
    else if (sf::Keyboard::Right){ //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
       // actor.spd = 50.0f;
        
       // ctrl.Dir(dirXY);
    }

    else if (sf::Keyboard::A){ //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
       // actor.spd = 50.0f;
       // ctrl.Dir(dirXY);
    }
     else if (sf::Keyboard::D){ //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
       // actor.spd = 50.0f;
       // ctrl.Dir(dirXY);
     }

    else if (sf::Keyboard::Left && sf::Keyboard::RShift){ //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
       // actor.spd = 75.0f;
       // ctrl.Dir(dirXY);
    }
    else if (sf::Keyboard::Right && sf::Keyboard::RShift){ //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
      // actor.spd = 75.0f;
       // ctrl.Dir(dirXY);
    }

    else if (sf::Keyboard::A && sf::Keyboard::RShift){ //|| sf::Keyboard::A:
        dirXY.x -= 1.0f;
      // actor.spd = 75.0f;
       // ctrl.Dir(dirXY);
    }
    else if (sf::Keyboard::D && sf::Keyboard::RShift){ //|| sf::Keyboard::D:
        dirXY.x += 1.0f;
        //actor.spd = 75.0f;
       // ctrl.Dir(dirXY);
    }
    
    actor.Dir( dirXY );
    


    actor.Timing(delta);

    win.clear();
    actor.Draw(win);
    win.display();
}
return EXIT_SUCCESS;
}