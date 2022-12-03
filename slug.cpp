    #include "slug.h"
    #include "lead.h"
    
	
	//void LoadUp();
	//void SlugFactory();
    sf::Vector2f wPos;
	sf::Vector2f plyPos;
	sf::RenderWindow* win;

	void Slug::WeaponPos(sf::Vector2f pos , sf::Vector2f plPos)
	{
	   wPos = pos;
	   plyPos = plPos;
	}
	
    void Win(sf::RenderWindow& r)
    {
       win = &r;
    }

	//void UpdateSlugs();
	void Slug::SlugFactory()
	{
		this->b["LEAD"] = new sf::Texture();
		this->b["LEAD"]->loadFromFile("bullet.png");
	}
	void Slug::Fire()
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->bullets.push_back(
				new Lead(
					this->b["LEAD"],
					wPos.x + plyPos.x/2.f,
					wPos.y + plyPos.y/2.f,
					0.f,
					-1.f,
					140.f
				)
			);
		}
	}

	void Slug::Update()
	{
        this->Fire();
		this->UpdateSlugs();
	}
	
	void Slug::UpdateSlugs()
	{
		unsigned count = 0;
		for (auto *bb  : this->bullets )
		{
			bb->Lead::UpdateBullet();
		
		if(bb->impact().top + bb->impact().height < 0.f)
		{
			delete this->bullets.at(count);
			this->bullets.erase(this->bullets.begin() + count);
		}
		++count;
	}
    }
    void Slug::Render()
	{
		for(auto *bb : this->bullets)
		{
			bb->Render(win);
		}
	}
    
    Slug::Slug()
    {
        this->SlugFactory();
    }
	Slug::~Slug()
	{
		for (auto *i : this->bullets)
		{
			delete i;
		}
	}