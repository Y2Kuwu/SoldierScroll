#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>

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
    int hei;
	int wid;
	View() = default;
	View( int x,int y,int wid,int hei,int viewNum,float wait )
		:
		wait( wait )
	{
		frames.reserve( viewNum );
		weaponFrames.reserve(viewNum);
		actorPtrToTex = Tex::AcquireActor( "actor.png" );
        assetPtrToTex = Tex::ActorAsset( "asset.png" );
        bgPtrToTex = Tex::AcquireActor( "bg.png" );
		for( int i = 0; i < viewNum; i++ )
		{
			frames.emplace_back( sf::Vector2i{ x,y },sf::Vector2i{ wid,hei } );
			x += wid;
		}
		for( int i = 0; i < viewNum; i++ )
		{
			weaponFrames.emplace_back( sf::Vector2i{ x,y },sf::Vector2i{ wid,hei } );
			x += wid;
		}
	}
	
	void SpritePaint( sf::Sprite& s) const //sf::Sprite& a sf::Sprite& bg
	{
		s.setTexture( *actorPtrToTex ); // a.setTexture( *ptrToTex ); b.setTexture( *ptrToTex );
		s.setTextureRect( frames[iFrame] ); // a.setTextureRect( frames[iFrame] ); bg.setTextureRect( frames[iFrame] );
		
	}
	void SpriteGun(sf::Sprite& a) const
	{
		a.setTexture( *assetPtrToTex );
		a.setTextureRect(weaponFrames[iFrame]);
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
	std::vector<sf::IntRect> weaponFrames;
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

        CrouchUp,
        CrouchDown,
        CrouchLeft,
        CrouchRight,

        //CrawlUp,
        //CrawlDown,
        //CrawlLeft,
        //CrawlRight,

        IdleCrouchUp,
		IdleCrouchDown,
		IdleCrouchLeft,
		IdleCrouchRight,

        //IdleCrawlUp,
		//IdleCrawlDown,
		//IdleCrawlLeft,
		//IdleCrawlRight,

		
		//PistolCrawlUp,
		//PistolCrawlRight,
		//PistolCrawlDown,

        //note: background images must stop on current frame and must be dependent on soldier movement



		Count
	};

	
	enum class RenderWeaponIdx : int{
		PistolFireUp = 0,
		PistolFireRight= 1,
		PistolFireDown= 2,
		PistolUp= 3,
		PistolRight= 4,
		PistolDown= 5,
		PistolCrouchUp= 6,
		PistolCrouchRight= 7,
		PistolCrouchDown= 8,

		RifleFireUp= 9,
		RifleFireRight= 10,
		RifleFireDown= 11,
		RifleUp= 12,
		RifleRight= 13,
		RifleDown= 14,
		RifleCrouchUp= 15,
		RifleCrouchRight= 16,
		RifleCrouchDown= 17,

		ShotgunFireUp= 18,
		ShotgunFireRight= 19,
		ShotgunFireDown= 20,
		ShotgunUp= 21,
		ShotgunRight= 22,
		ShotgunDown= 23,
		ShotgunCrouchUp= 24,
		ShotgunCrouchRight= 25,
		ShotgunCrouchDown= 26,

		Count
	};

	enum class RenderKitsIdx{
		Health,
		Armor,
		Ammo,
		Count
	};

	enum class RenderEnemyIdx{
		LightGoUp,
		LightGoDown,
		LightGoLeft,
		LightGoRight,

		LightIdleUp,
		LightIdleDown,
		LightIdleLeft,
		LightIdleRight,

		LightFireUp,
		LightFireDown,
		LightFireLeft,
		LightFireRight,

		MedGoUp,
		MedGoDown,
		MedGoLeft,
		MedGoRight,

		MedIdleUp,
		MedIdleDown,
		MedIdleLeft,
		MedIdleRight,

		MedFireUp,
		MedFireDown,
		MedFireLeft,
		MedFireRight,

		HeavyGoUp,
		HeavyGoDown,
		HeavyGoLeft,
		HeavyGoRight,

		HeavyIdleUp,
		HeavyIdleDown,
		HeavyIdleLeft,
		HeavyIdleRight,

		HeavyFireUp,
		HeavyFireDown,
		HeavyFireLeft,
		HeavyFireRight,

		Count
	};
	
		
//Char class public:
public:
	bool crouch = false;
	bool firing = false;
	int gunValue;
    float speed = 115.0f;
	float bulletSpeed = 140.0f;
	
	sf::RectangleShape bullet;


	sf::FloatRect playerBounds = sprite.getGlobalBounds();
	//sf::FloatRect healthKit = health.getGlobalBounds();
	//sf::FloatRect armorKit = armor.getGlobalBounds();
	//sf::FloatRect ammoKit = ammo.getGlobalBounds();
	//sf::FloatRect projHit = projectile.getGlobalBounds();

	
	
	std::map<RenderWeaponIdx, std::string> gunner;
	std::map<RenderWeaponIdx, std::string>::iterator gunn;

	std::string pistolSort = "Pistol";
    std::string rifleSort = "Rifle";
    std::string shotSort = "Shotgun";

	std::string weapon[3] = {pistolSort, rifleSort, shotSort};
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

        views[(int)RenderIdx::IdleCrouchUp] = View( 0,320,64,64,1,10.1f );
		views[(int)RenderIdx::IdleCrouchLeft] = View( 0,384,64,64,1,10.1f );
		views[(int)RenderIdx::IdleCrouchDown] = View( 0,448,64,64,1,10.1f );
		views[(int)RenderIdx::IdleCrouchRight] = View( 0,512,64,64,1,10.1f );

        // views[(int)RenderIdx::IdleCrawlUp] = View( 0,576,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrawlLeft] = View( 0,640,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrawlDown] = View( 0,704,64,64,1,10.1f );
		// views[(int)RenderIdx::IdleCrawlRight] = View( 0,768,64,64,1,10.1f );
            //

            //crawl crouch
        views[(int)RenderIdx::CrouchUp] = View( 64,320,64,64,8,0.1f );
		views[(int)RenderIdx::CrouchLeft] = View( 64,384,64,64,8,0.1f );
		views[(int)RenderIdx::CrouchDown] = View( 64,448,64,64,8,0.1f );
		views[(int)RenderIdx::CrouchRight] = View( 64,512,64,64,8,0.1f );

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
                //**PISTOL** // button #1 make default?
        
		gunViews[(int)RenderWeaponIdx::PistolFireUp] = View( 192,0,64,64,6,0.1f );
		gunViews[(int)RenderWeaponIdx::PistolFireRight] = View( 192,64,64,64,6,0.1f );
		gunViews[(int)RenderWeaponIdx::PistolFireDown] = View( 192,128,64,64,6,0.1f );

        gunViews[(int)RenderWeaponIdx::PistolUp] = View( 0,0,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::PistolRight] = View( 0,64,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::PistolDown] = View( 0,128,64,64,1,10.0f );

        gunViews[(int)RenderWeaponIdx::PistolCrouchUp] = View( 64,0,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::PistolCrouchRight] = View( 64,64,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::PistolCrouchDown] = View( 64,128,64,64,1,10.0f );


       // gunViews[(int)RenderIdx::PistolCrawlUp] = View( 128,0,64,64,1,10.0f );
		//gunViews[(int)RenderIdx::PistolCrawlRight] = View( 128,64,64,64,1,10.0f );
		//gunViews[(int)RenderIdx::PistolCrawlDown] = View( 128,128,64,64,1,10.0f );
                //
         //**RIFLE** // button #2 toggle
        gunViews[(int)RenderWeaponIdx::RifleFireUp] = View( 192,192,64,64,6,0.1f );
		gunViews[(int)RenderWeaponIdx::RifleFireRight] = View( 192,256,64,64,6,0.1f );
		gunViews[(int)RenderWeaponIdx::RifleFireDown] = View( 192,320,64,64,6,0.1f );
                //auto //       //make sure to end animations if not fired to corresponding idle animations
        // gunViews[(int)RenderWeaponIdx::AutoRifleFireUp] = View( 192,384,64,64,9,0.1f );
		// gunViews[(int)RenderWeaponIdx::AutoRifleFireRight] = View( 192,448,64,64,9,0.1f );
		// gunViews[(int)RenderWeaponIdx::AutoRifleFireDown] = View( 192,512,64,64,9,0.1f );
                //
        gunViews[(int)RenderWeaponIdx::RifleUp] = View( 0,192,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::RifleRight] = View( 0,256,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::RifleDown] = View( 0,320,64,64,1,10.0f );

        gunViews[(int)RenderWeaponIdx::RifleCrouchUp] = View( 64,192,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::RifleCrouchRight] = View( 64,256,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::RifleCrouchDown] = View( 64,320,64,64,1,10.0f );

        // gunViews[(int)RenderIdx::RifleCrawlUp] = View( 128,192,64,64,1,10.0f );
		// gunViews[(int)RenderIdx::RifleCrawlRight] = View( 128,256,64,64,1,10.0f );
		// gunViews[(int)RenderIdx::RifleCrawlDown] = View( 128,320,64,64,1,10.0f );
                //

                //
         //**SHOTGUN** // button #3 toggle
        gunViews[(int)RenderWeaponIdx::ShotgunFireUp] = View( 192,384,64,64,6,0.1f );
		gunViews[(int)RenderWeaponIdx::ShotgunFireRight] = View( 192,448,64,64,6,0.1f );
		gunViews[(int)RenderWeaponIdx::ShotgunFireDown] = View( 192,512,64,64,6,0.1f );

        gunViews[(int)RenderWeaponIdx::ShotgunUp] = View( 0,384,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::ShotgunRight] = View( 0,448,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::ShotgunDown] = View( 0,512,64,64,1,10.0f );

        gunViews[(int)RenderWeaponIdx::ShotgunCrouchUp] = View( 64,384,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::ShotgunCrouchRight] = View( 64,448,64,64,1,10.0f );
		gunViews[(int)RenderWeaponIdx::ShotgunCrouchDown] = View( 64,512,64,64,1,10.0f );

        // gunViews[(int)RenderIdx::RifleCrawlUp] = View( 128,384,64,64,1,10.0f );
		// gunViews[(int)RenderIdx::RifleCrawlRight] = View( 128,448,64,64,1,10.0f );
		// gunViews[(int)RenderIdx::RifleCrawlDown] = View( 128,512,64,64,1,10.0f );
                //
                    //add more below 

					//new page assets // enemy sprites
		kitViews[(int)RenderKitsIdx::Ammo] = View( 0,0,64,64,1,10.0f );
		kitViews[(int)RenderKitsIdx::Health] = View( 0,64,64,64,1,10.0f );
		kitViews[(int)RenderKitsIdx::Armor] = View( 0,128,64,64,1,10.0f );
		
	}
		
		

	void Draw( sf::RenderTarget& rt ) const
	{
		rt.draw( sprite );
		rt.draw( gunSprite );
	}
        //check which gun is called
	


    void CheckWeapon(const sf::Vector2f& dir)
    {			//use gun only when called 123 seperate functions?

		
		gunner[RenderWeaponIdx::PistolFireUp] = "PistolFireUp";
		gunner[RenderWeaponIdx::PistolFireDown] ="PistolFireDown";
		gunner[RenderWeaponIdx::PistolFireRight] = "PistolFireRight";
		gunner[RenderWeaponIdx::PistolUp] = "PistolUp";
		gunner[RenderWeaponIdx::PistolDown] = "PistolDown";
		gunner[RenderWeaponIdx::PistolRight] = "PistolRight";
		gunner[RenderWeaponIdx::PistolCrouchUp] = "PistolCrouchUp";
		gunner[RenderWeaponIdx::PistolCrouchDown] = "PistolCrouchDown";
		gunner[RenderWeaponIdx::PistolCrouchRight] = "PistolCrouchRight";

		gunner[RenderWeaponIdx::RifleFireUp] = "RifleFireUp";
		gunner[RenderWeaponIdx::RifleFireDown] ="RifleFireDown";
		gunner[RenderWeaponIdx::RifleFireRight] = "RifleFireRight";
		gunner[RenderWeaponIdx::RifleUp] = "RifleUp";
		gunner[RenderWeaponIdx::RifleDown] = "RifleDown";
		gunner[RenderWeaponIdx::RifleRight] = "RifleRight";
		gunner[RenderWeaponIdx::RifleCrouchUp] = "RifleCrouchUp";
		gunner[RenderWeaponIdx::RifleCrouchDown] = "RifleCrouchDown";
		gunner[RenderWeaponIdx::RifleCrouchRight] = "RifleCrouchRight";

		gunner[RenderWeaponIdx::ShotgunFireUp] = "ShotgunFireUp";
		gunner[RenderWeaponIdx::ShotgunFireDown] ="ShotgunFireDown";
		gunner[RenderWeaponIdx::ShotgunFireRight] = "ShotgunFireRight";
		gunner[RenderWeaponIdx::ShotgunUp] = "ShotgunUp";
		gunner[RenderWeaponIdx::ShotgunDown] = "ShotgunDown";
		gunner[RenderWeaponIdx::ShotgunRight] = "ShotgunRight";
		gunner[RenderWeaponIdx::ShotgunCrouchUp] = "ShotgunCrouchUp";
		gunner[RenderWeaponIdx::ShotgunCrouchDown] = "ShotgunCrouchDown";
		gunner[RenderWeaponIdx::ShotgunCrouchRight] = "ShotgunCrouchRight";



		velocity = dir * speed;
		std::string direction;
		std::string isFiring;
		std::string isCrouching;
		std::string weaponType;
		std::string match;
		//fire = firing;
		//gunValue = gun;
		
		//std::cout << gunValue-1;
		//crouching = crouch;
		weaponType = weapon[gunValue];

		bool headingRight = dir.x > 0.0f;
        bool headingLeft = dir.x < 0.0f;
        bool headingUp = dir.y < 0.0f;
        bool headingDown = dir.y > 0.0f;
        bool idlRight = velocity.x > 0.0f;
        bool idlLeft = velocity.x < 0.0f;
        bool idlUp = velocity.y < 0.0f;
        bool idlDown = velocity.y > 0.0f;

		//velocity = dir * speed;

		//////// MOVING WHILE NOT CROUCHING OR FIRING
		if(headingRight && firing == false && crouch == false)
		{
			direction = "Right";
			match = weaponType + direction;
		}
		else if(headingLeft && firing == false && crouch == false)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			match = weaponType + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(headingUp && firing == false && crouch == false)
		{
			direction = "Up";
			match = weaponType + direction;
		}
		else if(headingDown && firing == false && crouch == false)
		{
			direction = "Down";
			match = weaponType + direction;
		}
		//////// NOT MOVING WHILE NOT CROUCHING OR FIRING
		else{
			if(idlRight && firing == false && crouch == true)
		{
			direction = "Right";
			match = weaponType + direction;
		}
		else if(idlLeft && firing == false && crouch == true)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			match = weaponType + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(idlUp && firing == false && crouch == true)
		{
			direction = "Up";
			match = weaponType + direction;
		}
		else if(idlDown && firing == false && crouch == true)
		{
			direction = "Down";
			match = weaponType + direction;
		}
		//////// MOVING AND CROUCHING

		if(headingRight && crouch == true && firing == false)
		{
			direction = "Right";
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
		}
		else if(headingLeft && crouch == true && firing == false)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(headingUp && crouch == true && firing == false)
		{
			direction = "Up";
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
		}
		else if(headingDown && crouch == true && firing == false)
		{
			direction = "Down";
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
		}
		////// IDLE AND CROUCHING 
		else{
			if(idlRight && crouch == true && firing == false)
		{
			direction = "Right";
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
		}
		else if(idlLeft && crouch == true && firing == false)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(idlUp && crouch == true && firing == false)
		{
			direction = "Up";
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
		}
		else if(idlDown && crouch == true && firing == false)
		{
			direction = "Down";
			isCrouching = "Crouch";
			match = weaponType + isCrouching + direction;
		}
		else{
			///////CROUCHING AND FIRING WHILE *NOT* MOVING
			if(idlRight && crouch == true && firing == true)
		{
			direction = "Right";
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
		}
		else if(idlLeft && crouch == true && firing == true)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(idlUp && crouch == true && firing == true)
		{
			direction = "Up";
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
		}
		else if(idlDown && crouch == true && firing == true)
		{
			direction = "Down";
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
		}

		//
		else{
			///////CROUCHING AND FIRING WHILE MOVING
			if(headingRight && crouch == true && firing == true)
		{
			direction = "Right";
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
		}
		else if(headingLeft && crouch == true && firing == true)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(headingUp && crouch == true && firing == true)
		{
			direction = "Up";
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
		}
		else if(headingDown && crouch == true && firing == true)
		{
			direction = "Down";
			isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isCrouching + direction;
		}
		else{
			/////// STANDING AND FIRING
			if(headingRight && crouch == false && firing == true)
		{
			direction = "Right";
			//isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isFiring + direction;
		}
		else if(headingLeft && crouch == false && firing == true)
		{
			direction = "Right"; //remember to mirror sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
			//isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isFiring + direction;
			//gunSprite.setTextureRect(sf::IntRect(gunViews->wid, 0, -gunViews->wid, gunViews->hei));
		}
		else if(headingUp && crouch == false && firing == true)
		{
			direction = "Up";
			//isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isFiring + direction;
		}
		else if(headingDown && crouch == false && firing == true)
		{
			direction = "Down";
			//isCrouching = "Crouch";
			isFiring = "Fire";
			match = weaponType + isFiring + direction;
		}
		}
		}
		}
		}
		}
		
		 //gunvalue is reading accurately -1
		//match = weaponType + isFiring + isCrouching + direction;

		//std::cout<< weapon[gunValue-1];
		
		//match = weaponType + isFiring + direction;
		//match = weaponType + direction;
		//match = weaponType + isCrouching + direction;
		//std::cout << match;

		//ANIMATIONS HERE//
	  	
		for(gunn = gunner.begin(); gunn != gunner.end(); gunn++){
		if(match == gunn->second){
			std::cout << gunn->second; // grab second value
			currWepView = gunn->first; // grab first value 
		}
		}
		//std::cout << weapon[gunValue-1];
		//std::string gunSelect[] = {RenderIdx::Count};
		// for(int i =  int(RenderIdx::GoUp); i != int(RenderIdx::Count); i++)
		// {
		// 	i = std::find_if(pistolSort)
		// }
    }
	void GunCheck(int gun, const sf::Vector2f& dir)
	{
		gun = gunValue;
		//std::cout << gun;
	}

	void CrouchCheck(bool crouched, const sf::Vector2f& dir)
	{
		crouched = crouch;
		CheckWeapon(dir);
	}

	void FireCheck(bool fire, const sf::Vector2f& dir)
	{
		fire = firing;
		CheckWeapon(dir);
	}


	

        //check toggle for auto fire
    void CheckIfAuto(int clicked)
    {
        for(int clicked = 0; clicked < 2; clicked++){
            if(clicked %2 == 0){
                //set to auto
            }
        }
    }

   void MakeLead(int mag){//int magSize ){
		std::vector<sf::RectangleShape> bullets;
		bullets.reserve(mag); 
		
		std::cout << sprLoc.x; 
		std::cout << sprLoc.y;
   }

	

	//
	void SetDirection( const sf::Vector2f& dir )
	{
		if( dir.x > 0.0f ) //check for gunValue and proneValue
		{
			currView = RenderIdx::GoRight;
		}
		else if( dir.x < 0.0f )
		{
			currView = RenderIdx::GoLeft;
             //std::cout << headingRight; reading False 
		}
		else if( dir.y < 0.0f )
		{
			currView = RenderIdx::GoUp;
		}
		else if( dir.y > 0.0f )
		{
			currView = RenderIdx::GoDown;
		}
		//weapon movement animation
		else {
		if( dir.x > 0.0f ) 
		{
			
			//currView = RenderIdx:: 
			//RenderIdx currView = (RenderIdx)System.Enum.Parse(typeof(RenderIdx), dirSet);
			//std::map<std::string,std::string> fstring;
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

		//crouching animations
		else{
		if( dir.x > 0.0f && crouch == true)
		{
			currView = RenderIdx::CrouchRight;
            
		}
		else if( dir.x < 0.0f && crouch == true)
		{
			currView = RenderIdx::CrouchLeft;
		}
		else if( dir.y < 0.0f  && crouch == true)
		{
			currView = RenderIdx::CrouchUp;
		}
		else if( dir.y > 0.0f  && crouch == true)
		{
			currView = RenderIdx::CrouchDown;
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
		else
		{
			if( velocity.x > 0.0f && crouch == true)
			{
				currView = RenderIdx::IdleCrouchRight;
			}
			else if( velocity.x < 0.0f && crouch == true)
			{
				currView = RenderIdx::IdleCrouchLeft;
			}
			else if( velocity.y < 0.0f && crouch == true)
			{
				currView = RenderIdx::IdleCrouchUp;
			}
			else if( velocity.y > 0.0f && crouch == true)
			{
				currView = RenderIdx::IdleCrouchDown;
			}
		}
		}
		}
		}
		velocity = dir * speed;
	}
    
    
   

	void Update( float delta )
	{
		currPos += velocity * delta;
		views[int( currView )].Update( delta );
		views[int( currView )].SpritePaint( sprite);
		// copy function same mirror location
		// gunViews[int( currWepView )].Update( delta );
		// gunViews[int( currWepView )].SpriteGun( gunSprite);
		sprite.setPosition( currPos );
		//gunSprite.setPosition( currPos ); // if left flip/mirror sprite
	}

		void UpdateGun( float delta )
	{
		currPos += velocity * delta;
		//views[int( currView )].Update( delta );
		//views[int( currView )].SpritePaint( sprite);
		// copy function same mirror location
		gunViews[int( currWepView )].Update( delta );
		gunViews[int( currWepView )].SpriteGun( gunSprite);
		//sprite.setPosition( currPos );
		gunSprite.setPosition( currPos ); // if left flip/mirror sprite
	}
	
private:
	
    // acting as bool // change animation cycles
   
    int proneValue;
    int autoValue;
    //
	sf::Vector2f sprLoc = gunSprite.getPosition(); //get pos for weapon bullet origin

	sf::Vector2f currPos;
	sf::Vector2f velocity = {0.0f,0.0f};
	sf::Sprite sprite;
	sf::Sprite gunSprite;
	sf::Sprite kit;
	View views[int( RenderIdx::Count )];
	View gunViews[int( RenderWeaponIdx::Count )]; // within Char
	View kitViews[int( RenderKitsIdx::Count )];
	RenderIdx currView = RenderIdx::IdleRight;
	RenderWeaponIdx currWepView = RenderWeaponIdx::PistolRight;
};
class PlayerTracker{
public:
	int x;
	int y;
	

	int ammo; // array or vector?
	int ammoPIS = 25;
	int ammoSG = 5;
	int ammoRIF = 50;
	int health = 100;
	int armor = 0;

	int timeCount = 1;
	double timer = 0;

	//1 2 3
	double threeQuarter; //= .75; // adjust this for increments or add var below and divide by PER_SECS var
	
	clock_t time1 = clock();
	clock_t time2 = time1;

	sf::Text totAmmo;
	sf::Text totAmmoPIS;//
	sf::Text totAmmoRIF;//
	sf::Text totAmmoSG;//
	sf::Text totArmor;
	sf::Text totHealth;
	sf::RectangleShape stat;
	std::vector<sf::RectangleShape>projectile;
	sf::Font MG;
	

	PlayerTracker() = default;
	//PlayerTracker(int ammo, int health, int armor, sf::FloatRect player){
	void setTracker(){
		totAmmo.setCharacterSize(15);
		totAmmoPIS.setCharacterSize(10);
		totAmmoSG.setCharacterSize(10);
		totAmmoRIF.setCharacterSize(10);
		totArmor.setCharacterSize(15);
		totHealth.setCharacterSize(15);
		stat.setSize(sf::Vector2f(200.f,100.f));
		stat.setPosition(500.f,20.f);
		stat.setFillColor(sf::Color::Transparent);
		stat.setOutlineColor(sf::Color::Red);
		stat.setOutlineThickness(5);
		MG.loadFromFile("MGS2.ttf");
		totAmmo.setFont(MG);
		totAmmoPIS.setFont(MG);
		totAmmoSG.setFont(MG);
		totAmmoRIF.setFont(MG);
		totArmor.setFont(MG);
		totHealth.setFont(MG);

		totAmmo.setFillColor(sf::Color::Red);

		totAmmoPIS.setFillColor(sf::Color::Red);
		totAmmoRIF.setFillColor(sf::Color::Red);
		totAmmoSG.setFillColor(sf::Color::Red);

		totArmor.setFillColor(sf::Color::Red);
		totHealth.setFillColor(sf::Color::Red);

		//totAmmo.setOutlineColor(sf::Color::Yellow);
		//totArmor.setOutlineColor(sf::Color::White);
		//totHealth.setOutlineColor(sf::Color::Green);
		//change color on damage, pickup, etc.
		//totAmmo.setOutlineThickness(2);
		//totArmor.setOutlineThickness(2);
		//totHealth.setOutlineThickness(2);

		totAmmo.setPosition(510.f,35.f);

		totAmmoPIS.setPosition(510.f,50.f);
		totAmmoRIF.setPosition(510.f,60.f);
		totAmmoSG.setPosition(510.f,70.f);

		totArmor.setPosition(570.f,35.f);
		totHealth.setPosition(630.f,35.f);
		totAmmo.setString("Ammo:");

		totAmmoPIS.setString("Pistol: " + std::to_string(ammoPIS));
		totAmmoRIF.setString("Rifle: " + std::to_string(ammoRIF));
		totAmmoSG.setString("ShotGun: " + std::to_string(ammoSG));

		totArmor.setString("Armor: " + std::to_string(armor));
		totHealth.setString("Health: " + std::to_string(health));
	}
	// void NapTime(unsigned int t){ . // take in weapon type and return sleep time per shot
		
	// }
	 //d = std::chrono::milliseconds();
	// void TrackAmmo(std::chrono::milliseconds()){ 
	// 	ammo -= 1 / std::chrono::milliseconds();
	// }
	void TrackAllAmmo(int ps , int rf, int sg){
		ammo = ps + rf + sg;
	}

	void TrackAmmo(int g){
		// if(gun == 1){
		// 	threeQuarter = .75;
		// 	ammoPIS;
		// }
		// if(gun == 2){
		// 	threeQuarter = .2;
		// 	ammoRIF;
		// }
		// if(gun == 3){
		// 	threeQuarter = 1.2;
		// 	ammoSG;
		// }
		//std::cout << gun;
		
		time1 = clock(); 
		timer += (double)(time1 - time2);
		time2 = time1;

		if(timer > (double)(threeQuarter * CLOCKS_PER_SEC) && g == 1)
		{
			threeQuarter = .75;
			timer -= (double)(threeQuarter * CLOCKS_PER_SEC);
			timeCount++;
			ammoPIS -= 1; // ammo type 1 , 2 , 3
		}
		else if(timer > (double)(threeQuarter * CLOCKS_PER_SEC) && g == 2)
		{
			threeQuarter = .2;
			timer -= (double)(threeQuarter * CLOCKS_PER_SEC);
			timeCount++;
			ammoRIF -= 1; // ammo type 1 , 2 , 3
		}
		else if(timer > (double)(threeQuarter * CLOCKS_PER_SEC) && g == 3)
		{
			threeQuarter = .95;
			timer -= (double)(threeQuarter * CLOCKS_PER_SEC);
			timeCount++;
			ammoSG -= 1; // ammo type 1 , 2 , 3
		}
		TrackAllAmmo(ammoPIS , ammoRIF, ammoSG);
		//std::cout << ammo;
	}

	void DrawTracker( sf::RenderTarget& ren )const
	{
		ren.draw(stat);
		ren.draw(totAmmo);
		ren.draw(totAmmoPIS);
		ren.draw(totAmmoRIF);
		ren.draw(totAmmoSG);
		ren.draw(totArmor);
		ren.draw(totHealth);
	}

};


int main()
{
    //bool isShift = false;
	// Create the main window
	sf::RenderWindow window( sf::VideoMode( 800,600 ),"SFML window" );

	{
		Char soldier( { 100.0f,100.0f } );
		Char soldierCorpse( { 100.0f,200.0f } );
		Char weapon ({20.0f,20.0f});
		Char weaponEmpty ({20.0f,40.0f});

		
	}

	Tex::clearPtr();
	PlayerTracker status;

	Char soldier( { 100.0f,100.0f } );
	Char weapon ( { 10.0f, 100.0f } );
	// timepoint for delta time measurement
	auto tp = std::chrono::steady_clock::now();
	auto dl = std::chrono::steady_clock::now();

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
		float deltaLong;
		auto dlong= std::chrono::milliseconds(900);
		//float dlong = 4000;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			delta = std::chrono::duration<float>( new_tp - tp ).count();
			tp = new_tp;

			

		}

		// make into switch cases?
		sf::Vector2f dir = { 0.0f,0.0f };
        int autoCheck = 0;
		int gun;
		//int crouching = 1;
        if (sf::Keyboard::isKeyPressed( sf::Keyboard::LControl) ){
            soldier.speed = 0.0f;
			weapon.speed = 0.0f;
                //aim
			soldier.CheckWeapon(dir);
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space) )
		{
			soldier.firing = true;
			//soldier.CheckWeapon(dir);
			//soldier.GunCheck(gun);
			soldier.FireCheck(soldier.firing, dir);
			//const auto new_dl = std::chrono::steady_clock::now();
			
			
			status.TrackAmmo(gun);
			//std::cout << status.ammo; total quantity 
			status.setTracker();
			status.DrawTracker( window );
			}
		

		//while (sf::Keyboard::isKeyPressed( sf::Keyboard::Space))
		//{
			//float second = .998;
			//this_thread::sleep_for(chrono::milliseconds(1000));
			
			//float countFire;
			//const auto fireSet = std::chrono::steady_clock::now();
			//status.NapTime(0.99);
			//std::this_thread::sleep_for(std::chrono::milliseconds(150));
			//auto fireStop = std::chrono::steady_clock::now();
			//countFire =  std::chrono::duration<float>(fireSet - fireStop).count(); 

			//if(countFire = float_sec){
			//soldier.Update(delta);
			
			
		    
			
			//}
		//}
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed( sf::Keyboard::LShift) ){
            soldier.speed = 200.0f;
			weapon.speed = 200.0f;
			soldier.CheckWeapon(dir);
        }
		else if (event.type == sf::Event::KeyReleased){
			soldier.speed = 115.0f;
			weapon.speed = 115.0f;
			
		}
       
	   
       if ( sf::Keyboard::isKeyPressed( sf::Keyboard::C)){
		
			soldier.crouch = true;
           //soldier.Stealth(prone);
		    soldier.CrouchCheck(soldier.crouch, dir);
			soldier.speed = 75.0f;
			weapon.speed = 75.0f;
			
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		{
			dir.y -= 1.0f;
			 soldier.CheckWeapon(dir);
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		{
			dir.y += 1.0f;
			 soldier.CheckWeapon(dir);
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		{
			dir.x -= 1.0f;
			 soldier.CheckWeapon(dir);
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		{
			dir.x += 1.0f;
			 soldier.CheckWeapon(dir);
		}
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		{
			dir.y -= 1.0f;
			 soldier.CheckWeapon(dir);
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		{
			dir.y += 1.0f;
			soldier.CheckWeapon(dir);
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		{
			dir.x -= 1.0f;
			 soldier.CheckWeapon(dir);
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		{
			dir.x += 1.0f;
			 soldier.CheckWeapon(dir);
		}
        // NUM check weapon
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1) )
		{
		   gun = 1;
           //soldier.CheckWeapon(dir);
		
		   soldier.GunCheck(gun, dir) ;
		}

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num2) )
		{
			gun = 2;
			//soldier.CheckWeapon(dir);
			soldier.GunCheck(gun, dir);
		
           // soldier.CheckIfAuto(autoCheck);
		}

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num3) )
		{
			gun = 3;
			//soldier.CheckWeapon(dir);
			soldier.GunCheck(gun, dir);
		
		}
		
        
		
		soldier.SetDirection( dir );
		weapon.SetDirection( dir );

		// update 
		soldier.Update( delta );
		weapon.UpdateGun( delta );
		//weapon.MakeLead();
		// clear 
		window.clear();
		// draw
		status.DrawTracker( window );
		soldier.Draw( window );
		weapon.Draw( window );
		status.setTracker(); // track status of player
		status.DrawTracker( window );
		
		
		// update window
		window.display();
	}
	return EXIT_SUCCESS;
}
