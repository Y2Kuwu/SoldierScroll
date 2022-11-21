#ifndef TEX_H
#define TEX_H
#include "controller.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <memory>


class Tex {
    public:
    Tex() = default;
            //returning shared_ptr
    static std::shared_ptr<sf::Texture> Tex::loadActor( const std::string& texName );
    static std::shared_ptr<sf::Texture> Tex::loadPassive( const std::string& background );
    static std::shared_ptr<sf::Texture> Tex::loadAsset( const std::string& asset );
    static void ErasePrev();

    private:
                    
        static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> texConnect; 
        static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> worldConnect; 
        static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> assetConnect;  

};
 static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> texConnect; 
 static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> worldConnect; 
 static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> assetConnect;

    class View
    {
        
        public:
        View() = default;

        

        View(int posX , int posY , int totHeight, int totWidth, int currView, float wait)
         :
        wait(wait)
        {
         

         actorTexture = Tex::loadActor("actor.png");
         worldTexute = Tex::loadPassive("world.png");
         assetTexture = Tex::loadAsset("asset.png");
         for(int s = 0; s < storeFrames.size(); s++){
             storeFrames.insert(storeFrames.end(), { sf::Vector2i{ posX,posY },sf::Vector2i{ totWidth,totHeight } } );
             posX += totWidth;
         }
        }
      
       
        
            //set up for actor for now 
            //add additional later or link all
    void makeSprite(sf::Sprite& actor , sf::Sprite& world, sf::Sprite& asset){
        actor.setTexture( *actorTexture );
        actor.setTextureRect ( storeFrames[current] );
    }
        //delta defined in main
    void TimingBelt(float delta){
        time += delta;
        while (time >= wait)
        {
            time -= wait;
            Next();
        }
    }


    private:
        void Next(){
            if(++current >= storeFrames.size())
            {
                current = 0;
            }
        }


        std::vector<sf::IntRect> storeFrames;
        //
        std::shared_ptr<sf::Texture> worldTexute;
        std::shared_ptr<sf::Texture> assetTexture;
        std::shared_ptr<sf::Texture> actorTexture;
        //
        int current = 0;
        float wait;     // wait compared to time (time idle)
        float time = 0.0f; // compared to wait in ms

    };



#endif