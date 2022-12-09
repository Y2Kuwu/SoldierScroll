// #include "invader.h"


// void Invader::SetVars()
// {
//     this->mainCounter;
//     this->type = 0;
//     this->spd =  2;
//     this->health = 100;
//     this->dmg = this->mainCounter;
//     this->count = this->mainCounter;
// }

// void Invader::SetTexture()
// {
//     this->inv.setOrigin(px,py);

// }

// Invader::Invader(float px, float py, float spd)
// {
//     this->SetVars();
//     this->SetTexture();

//     this->inv.setPosition(px,py);
// }



// const sf::FloatRect Invader::InvBox() const
// {
//     return this->inv.getGlobalBounds();
// }

// const int & Invader::PointCount()const
// {
//     return this->count;
// }

// const int & Invader::DmgTaken()const
// {
//     return this->dmg;
// }

// void Invader::UpdateInv()
// {
//     this->inv.move(0.0f, this->spd);
// }

// void Invader::RenderInv(sf::RenderTarget *rt)
// {
//     rt->draw(this->inv);
// }
