#ifndef SLUG_H
#define SLUG_H
#include<map>
#include<string>
#include "lead.h"

class Slug
{
    private:
    std::map<std::string, sf::Texture*> b;
	std::vector<Lead*> bullets;
    //sf::RenderWindow* win;
    
    public:

   

    Slug();
    virtual ~Slug();
    void SlugFactory();
    void Fire();
    void UpdateSlugs();
    void Update();
    void Render();
    void Win();
    void WeaponPos(sf::Vector2f p , sf::Vector2f pl);
};

#endif