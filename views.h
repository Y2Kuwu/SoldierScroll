// #ifndef VIEWS_H
// #define VIEWS_H
// #include "tex.h"
// #include <vector>


//  class Views
//     {
        
//         public:
        
//        Views() = default;
//         Views(int posX , int posY , int totWidth, int totHeight, int currView, float wait)
//          :
//          wait( wait )
//         {
//         sframes.reserve(currView);
//         actorTexture = Tex::LoadActor("actor.png");
//         //  actorTexture = Tex::loadActor("actor.png");
//         //  worldTexute = Tex::loadPassive("world.png");
//         //  assetTexture = Tex::loadAsset("asset.png");
        
//          for(int s = 0; s < currView; s++)
//          {
//              sframes.emplace_back( sf::Vector2i{ posX,posY },sf::Vector2i{ totWidth,totHeight });
//              posX += totWidth;
//          }
//         }
      
       
        
//             //set up for actor for now 
//             //add additional later or link all
//     void makeSprite(sf::Sprite& sp) const 
//     { //, sf::Sprite& world, sf::Sprite& asset){
//         sp.setTexture( *actorTexture );
//         sp.setTextureRect ( sframes[current] );
//     }
//         //delta defined in main
//     void TimingBelt(float delta){
//         time += delta;
//         while (time >= wait)
//         {
//             time -= wait;
//             Next();
//         }
//     }


//     private:
//         void Next(){
//             if(++current >= int (sframes.size() ) )
//             {
//                 current = 0;
//             }
//         }
//     private:

//         std::vector<sf::IntRect> sframes;
//         //
//         //std::shared_ptr<sf::Texture> worldTexute;
//        //std::shared_ptr<sf::Texture> assetTexture;
//         std::shared_ptr<sf::Texture> actorTexture;
//         //
//         int current = 0;
//         float wait;     // wait compared to time (time idle)
//         float time = 0.0f; // compared to wait in ms

//     };
// #endif 


