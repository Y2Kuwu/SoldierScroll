#ifndef VIEWS_H
#define VIEWS_H
#include "controller.h"


 class Views
    {
        
        public:
        Views() = default;

        Views(int posX , int posY , int totHeight, int totWidth, int currView, float wait)
         :
        wait(wait)
        {
         

        //  actorTexture = Tex::loadActor("actor.png");
        //  worldTexute = Tex::loadPassive("world.png");
        //  assetTexture = Tex::loadAsset("asset.png");
         for(int s = 0; s < storeFrames.size(); s++){
             storeFrames.insert(storeFrames.end(), { sf::Vector2i{ posX,posY },sf::Vector2i{ totWidth,totHeight } } );
             posX += totWidth;
         }
        }
      
       
        
            //set up for actor for now 
            //add additional later or link all
    void makeSprite(sf::Sprite& actor){ //, sf::Sprite& world, sf::Sprite& asset){
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