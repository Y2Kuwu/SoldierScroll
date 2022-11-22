#include "controller.h"
#include "tex.h"
#include <iostream>

int main(){
    
    Tex tex;

    sf::RenderWindow win( sf::VideoMode( 800,600 ),"SFML window" );

	{
		Controller actor( { 100.0f,100.0f } );
		Controller actorClone( { 100.0f,200.0f } );
	}

    tex.ErasePrev();

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

    win.clear();
    actor.timingBelt(delta);
    win.display();
}
return EXIT_SUCCESS;
}