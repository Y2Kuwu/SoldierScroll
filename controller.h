// #ifndef CONTROLLER_H
// #define CONTROLLER_H
// #include "views.h"
// #include "tex.h"
// class Controller
// {
// public:
// Controller() = default;
// Controller(const sf::Vector2f& currPos): currPos(currPos){
//     moving[(int)RenderIdx::GoRight] = Views(64,192,64,64,8,0.1f);
//     moving[(int)RenderIdx::GoLeft] = Views(64,64,64,64,8,0.1f);
//    // moving[(int)RenderIdx::Crouch] = View();
//    // moving[(int)RenderIdx::Crawl] = View();

//     moving[(int)RenderIdx::IdleRight] = Views(0,192,64,64,1,10.1f);
//     moving[(int)RenderIdx::IdleLeft] = Views(0,64,64,64,1,10.1f);
//                                         //view class
// };

// //void init();
// void capControls();
// void Timing( float delta );
// void Draw(sf::RenderTarget& render);
// void Dir (sf::Vector2f& dirXY);


// private:
//     enum class RenderIdx{
//     GoRight,
//     GoLeft,
//     Crouch,
//     Crawl,

//     IdleRight,
//     IdleLeft,

//     Count 

// };


// bool gameIsStarted;

// float spd = 50.0f; // if shift * 1.5;
// sf::Vector2f currPos;
// sf::Vector2f velocity = {0.0f,0.0f};
// sf::Sprite spr;
// Views moving[int( RenderIdx::Count )];
// RenderIdx act = RenderIdx::IdleRight;
// sf::Event evt;
//     //View class

  
    

// };



// #endif