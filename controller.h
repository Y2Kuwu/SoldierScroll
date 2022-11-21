#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SFML/Window.hpp>
class Controller
{
public:
Controller() = default;
//Controller( const sf::Vector2f& currPos);



void init();
void capControls();
enum RenderIdx{};

private:
    enum class RenderIdx{

    GoRight,
    GoLeft,
    Crouch,
    Crawl,
    Count 

};


bool gameIsStarted;
enum RenderIdx{};
sf::Vector2f currPos;
sf::Vector2f velocity;
sf::Sprite spr;
Controller moving[int( RenderIdx::Count )];

};

#endif