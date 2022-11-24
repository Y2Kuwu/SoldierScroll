#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

class Tex
{
public:
        //soldier 
	static std::shared_ptr<sf::Texture> AcquireActor( const std::string& actorName )
	{
		const auto i = actorPtr.find( actorName );
		if( i != actorPtr.end() )
		{
			return i->second;
		}
		else
		{
			auto actorPtrToTex = std::make_shared<sf::Texture>();
			actorPtrToTex->loadFromFile( actorName );
			actorPtr.insert( { actorName,actorPtrToTex } );
			return actorPtrToTex;
		}
	}
        //assets owned by soldier 
    static std::shared_ptr<sf::Texture> ActorAsset( const std::string& assetName )
	{
		const auto a = assetPtr.find( assetName );
		if( a != assetPtr.end() )
		{
			return a->second;
		}
		else
		{
			auto assetPtrToTex = std::make_shared<sf::Texture>();
			assetPtrToTex->loadFromFile( assetName );
			assetPtr.insert( { assetName,assetPtrToTex } );
			return assetPtrToTex;
		}
	}
        //background assets
     static std::shared_ptr<sf::Texture> BackGround( const std::string& bgName )
	{
		const auto a = bgPtr.find( bgName );
		if( a != bgPtr.end() )
		{
			return a->second;
		}
		else
		{
			auto bgPtrToTex = std::make_shared<sf::Texture>();
			bgPtrToTex->loadFromFile( bgName );
			assetPtr.insert( { bgName,bgPtrToTex } );
			return bgPtrToTex;
		}
	}
        
	static void clearPtr()
	{   
            //ptr eraser for soldier
		for( auto act = actorPtr.begin(); act != actorPtr.end(); )
		{
			if( act->second.unique() )
			{
				act = actorPtr.erase( act );
			}
			else
			{
				++act;
			}
		}
            //ptr erase for soldier assets
        for( auto set = assetPtr.begin(); set != assetPtr.end(); )
		{
			if( set->second.unique() )
			{
				set = assetPtr.erase( set );
			}
			else
			{
				++set;
			}
		}
            //ptr for background assets
        for( auto bg = bgPtr.begin(); bg != bgPtr.end(); )
		{
			if( bg->second.unique() )
			{
				bg = bgPtr.erase( bg );
			}
			else
			{
				++bg;
			}
		}
	}
private:
	static std::unordered_map<std::string,std::shared_ptr<sf::Texture>> actorPtr;
    static std::unordered_map<std::string,std::shared_ptr<sf::Texture>> assetPtr;
    static std::unordered_map<std::string,std::shared_ptr<sf::Texture>> bgPtr;
};

std::unordered_map<std::string,std::shared_ptr<sf::Texture>> Tex::actorPtr;
std::unordered_map<std::string,std::shared_ptr<sf::Texture>> Tex::assetPtr;
std::unordered_map<std::string,std::shared_ptr<sf::Texture>> Tex::bgPtr;

class View
{
public:
    

	View() = default;
	View( int x,int y,int wid,int hei,int viewNum,float wait )
		:
		wait( wait )
	{
		frames.reserve( viewNum );
		actorPtrToTex = Tex::AcquireActor( "actor.png" );
        assetPtrToTex = Tex::AcquireActor( "asset.png" );
        bgPtrToTex = Tex::AcquireActor( "bg.png" );
		for( int i = 0; i < viewNum; i++ )
		{
			frames.emplace_back( sf::Vector2i{ x,y },sf::Vector2i{ wid,hei } );
			x += wid;
		}
	}
	void SpritePaint( sf::Sprite& s ) const //sf::Sprite& a sf::Sprite& bg
	{
		s.setTexture( *actorPtrToTex ); // a.setTexture( *ptrToTex ); b.setTexture( *ptrToTex );
		s.setTextureRect( frames[iFrame] ); // a.setTextureRect( frames[iFrame] ); bg.setTextureRect( frames[iFrame] );
	}
	void Update( float delta )
	{
		time += delta;
		while( time >= wait )
		{
			time -= wait;
			RendNext();
		}
	}
private:
	void RendNext()
	{
		if( ++iFrame >= int( frames.size() ) )
		{
			iFrame = 0;
		}
	}
private:
	float wait;
	std::shared_ptr<sf::Texture> actorPtrToTex;
    std::shared_ptr<sf::Texture> assetPtrToTex;
    std::shared_ptr<sf::Texture> bgPtrToTex;
	std::vector<sf::IntRect> frames;
	int iFrame = 0;
	float time = 0.0f;
};

class Char
{
private:
	enum class RenderIdx
	{
		GoUp,
		GoDown,
		GoLeft,
		GoRight,

		IdleUp,
		IdleDown,
		IdleLeft,
		IdleRight,

        //AimUp,
        //AimDown,
        //AimLeft,
        //AimRight,

        //CrouchUp,
        //CrouchDown,
        //CrouchLeft,
        //CrouchRight,

        //CrawlUp,
        //CrawlDown,
        //CrawlLeft,
        //CrawlRight,

        //IdleCrouchUp,
		//IdleCrouchDown,
		//IdleCrouchLeft,
		//IdleCrouchRight,

        //IdleCrawlUp,
		//IdleCrawlDown,
		//IdleCrawlLeft,
		//IdleCrawlRight,

        //note: background images must stop on current frame and must be dependent on soldier movement



		Count
	};
public:
    float speed = 75.0f;
	Char( const sf::Vector2f& currPos )
		:
		currPos( currPos )
	{                                   
        //from actor.png                     //starting at 
        //{
		views[(int)RenderIdx::GoUp] = View( 64,0,64,64,8,0.1f );
		views[(int)RenderIdx::GoLeft] = View( 64,64,64,64,8,0.1f );
		views[(int)RenderIdx::GoDown] = View( 64,128,64,64,8,0.1f );
		views[(int)RenderIdx::GoRight] = View( 64,192,64,64,8,0.1f );
		views[(int)RenderIdx::IdleUp] = View( 0,0,64,64,1,10.1f );
		views[(int)RenderIdx::IdleLeft] = View( 0,64,64,64,1,10.1f );
		views[(int)RenderIdx::IdleDown] = View( 0,128,64,64,1,10.1f );
		views[(int)RenderIdx::IdleRight] = View( 0,192,64,64,1,10.1f );

            //idle animations 
        //Aim + LCtrl //stops movement
            //all one row one frame each
        // views[(int)RenderIdx::AimUp] = View( 0,256,64,64,1,10.1f );
		// views[(int)RenderIdx::AimLeft] = View( 64,256,64,64,1,10.1f );
		// views[(int)RenderIdx::AimDown] = View( 128,256,64,64,1,10.1f );
		// views[(int)RenderIdx::AimRight] = View( 192,256,64,64,1,10.1f );

        // views[(int)RenderIdx::IdleCrouchUp] = View( 0,320,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrouchLeft] = View( 0,384,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrouchDown] = View( 0,448,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrouchRight] = View( 0,512,64,64,1,10.1f );

        // views[(int)RenderIdx::IdleCrawlUp] = View( 0,576,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrawlLeft] = View( 0,640,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrawlDown] = View( 0,704,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrawlRight] = View( 0,768,64,64,1,10.1f );
            //

            //crawl crouch
        // views[(int)RenderIdx::CrouchUp] = View( 64,320,64,64,8,0.1f );
		// views[(int)RenderIdx::CrouchLeft] = View( 64,384,64,64,8,0.1f );
		// views[(int)RenderIdx::CrouchDown] = View( 64,448,64,64,8,0.1f );
		// views[(int)RenderIdx::CrouchRight] = View( 64,512,64,64,8,0.1f );

        // views[(int)RenderIdx::CrouchUp] = View( 64,576,64,64,8,0.1f );
		// views[(int)RenderIdx::CrouchLeft] = View( 64,640,64,64,8,0.1f );
		// views[(int)RenderIdx::CrouchDown] = View( 64,704,64,64,8,0.1f );
		// views[(int)RenderIdx::CrouchRight] = View( 64,768,64,64,8,0.1f );
            //
            //}
            //from actorAssets.png{
                //asset/weapon animations
                //note:: maybe try mirroring sprite instead of drawing left and right 
                //sprite.setScale({-1,1});
                //**PISTOL** // button #1 toggle or make default?
        // views[(int)RenderIdx::PistolFireUp] = View( 192,0,64,64,6,0.1f );
		// views[(int)RenderIdx::PistolFireRight] = View( 192,64,64,64,6,0.1f );
		// views[(int)RenderIdx::PistolFireDown] = View( 192,128,64,64,6,0.1f );

        // views[(int)RenderIdx::PistolIdleUp] = View( 0,0,64,64,1,10.0f );
		// views[(int)RenderIdx::PistolIdleRight] = View( 0,64,64,64,1,10.0f );
		// views[(int)RenderIdx::PistolIdleDown] = View( 0,128,64,64,1,10.0f );

        // views[(int)RenderIdx::PistolCrouchUp] = View( 64,0,64,64,1,10.0f );
		// views[(int)RenderIdx::PistolCrouchRight] = View( 64,64,64,64,1,10.0f );
		// views[(int)RenderIdx::PistolCrouchDown] = View( 64,128,64,64,1,10.0f );

        // views[(int)RenderIdx::PistolCrawlUp] = View( 128,0,64,64,1,10.0f );
		// views[(int)RenderIdx::PistolCrawlRight] = View( 128,64,64,64,1,10.0f );
		// views[(int)RenderIdx::PistolCrawlDown] = View( 128,128,64,64,1,10.0f );
                //
         //**RIFLE** // button #2 toggle
        // views[(int)RenderIdx::RifleFireUp] = View( 192,192,64,64,6,0.1f );
		// views[(int)RenderIdx::RifleFireRight] = View( 192,256,64,64,6,0.1f );
		// views[(int)RenderIdx::RifleFireDown] = View( 192,320,64,64,6,0.1f );

        // views[(int)RenderIdx::RifleIdleUp] = View( 0,192,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleIdleRight] = View( 0,256,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleIdleDown] = View( 0,320,64,64,1,10.0f );

        // views[(int)RenderIdx::RifleCrouchUp] = View( 64,192,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrouchRight] = View( 64,256,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrouchDown] = View( 64,320,64,64,1,10.0f );

        // views[(int)RenderIdx::RifleCrawlUp] = View( 128,192,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrawlRight] = View( 128,256,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrawlDown] = View( 128,320,64,64,1,10.0f );
                //

                //
         //**SHOTGUN** // button #3 toggle
        // views[(int)RenderIdx::RifleFireUp] = View( 192,384,64,64,6,0.1f );
		// views[(int)RenderIdx::RifleFireRight] = View( 192,448,64,64,6,0.1f );
		// views[(int)RenderIdx::RifleFireDown] = View( 192,512,64,64,6,0.1f );

        // views[(int)RenderIdx::RifleIdleUp] = View( 0,384,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleIdleRight] = View( 0,448,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleIdleDown] = View( 0,512,64,64,1,10.0f );

        // views[(int)RenderIdx::RifleCrouchUp] = View( 64,384,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrouchRight] = View( 64,448,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrouchDown] = View( 64,512,64,64,1,10.0f );

        // views[(int)RenderIdx::RifleCrawlUp] = View( 128,384,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrawlRight] = View( 128,448,64,64,1,10.0f );
		// views[(int)RenderIdx::RifleCrawlDown] = View( 128,512,64,64,1,10.0f );
                //
                    //add more below 






		
        




	}
	void Draw( sf::RenderTarget& rt ) const
	{
		rt.draw( sprite );
	}
    
   

	void SetDirection( const sf::Vector2f& dir )
	{
		if( dir.x > 0.0f )
		{
            
			currView = RenderIdx::GoRight;
          
		}
		else if( dir.x < 0.0f )
		{
          
			currView = RenderIdx::GoLeft;
		}
		else if( dir.y < 0.0f )
		{
          
			currView = RenderIdx::GoUp;
		}
		else if( dir.y > 0.0f )
		{
         
			currView = RenderIdx::GoDown;
		}
    //
     
        //
		else
		{
			if( velocity.x > 0.0f )
			{
				currView = RenderIdx::IdleRight;
			}
			else if( velocity.x < 0.0f )
			{
				currView = RenderIdx::IdleLeft;
			}
			else if( velocity.y < 0.0f )
			{
				currView = RenderIdx::IdleUp;
			}
			else if( velocity.y > 0.0f )
			{
				currView = RenderIdx::IdleDown;
			}
            
		}
		velocity = dir * speed;
	}
    
    
   

	void Update( float delta )
	{
		currPos += velocity * delta;
		views[int( currView )].Update( delta );
		views[int( currView )].SpritePaint( sprite );
		sprite.setPosition( currPos );
	}
private:
	
    

	sf::Vector2f currPos;
	sf::Vector2f velocity = {0.0f,0.0f};
	sf::Sprite sprite;
	View views[int( RenderIdx::Count )];
	RenderIdx currView = RenderIdx::IdleRight;
};

int main()
{
    bool isShift = false;
	// Create the main window
	sf::RenderWindow window( sf::VideoMode( 800,600 ),"SFML window" );

	{
		Char soldier( { 100.0f,100.0f } );
		Char soldierCorpse( { 100.0f,200.0f } );
	}

	Tex::clearPtr();

	Char soldier( { 100.0f,100.0f } );

	// timepoint for delta time measurement
	auto tp = std::chrono::steady_clock::now();

	// Start the game loop
	while( window.isOpen() )
	{
		// Process events
		sf::Event event;
		while( window.pollEvent( event ) )
		{
			// Close window: exit
			if( event.type == sf::Event::Closed )
				window.close();
		}

		// get delta
		float delta;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			delta = std::chrono::duration<float>( new_tp - tp ).count();
			tp = new_tp;
		}


		// handle input
		sf::Vector2f dir = { 0.0f,0.0f };
         if (sf::Keyboard::isKeyPressed( sf::Keyboard::LControl) ){
            soldier.speed = 0.0f;
        }

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::LShift) ){
            soldier.speed = 200.0f;
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		{
			dir.y -= 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		{
			dir.y += 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		{
			dir.x -= 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		{
			dir.x += 1.0f;
		}
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		{
			dir.y -= 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		{
			dir.y += 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		{
			dir.x -= 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		{
			dir.x += 1.0f;
		}
        
		
		soldier.SetDirection( dir );
		

		// update model
		soldier.Update( delta );

		// Clear screen
		window.clear();
		// Draw the sprite
		soldier.Draw( window );
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}