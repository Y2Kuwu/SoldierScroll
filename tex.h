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

        std::vector<sf::Vector2i> storeFrames;

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
      
       
        
        
    void makeSprite(sf::Sprite& actor , sf::Sprite& world, sf::Sprite& asset){
        actor.setTexture( *actorTexture );
        actor.setTextureRect ( storeFrames );
    }
        
    private:
        std::shared_ptr<sf::Texture> worldTexute;
        std::shared_ptr<sf::Texture> assetTexture;
        std::shared_ptr<sf::Texture> actorTexture;
        int current;

    };



#endif