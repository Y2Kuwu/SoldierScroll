#include "tex.h"


static std::shared_ptr<sf::Texture> loadActor( const std::string& texName ){ 
        const auto texFind = texConnect.find( texName );
        if( texFind != texConnect.end())
        {
            return texFind->second; 
        }
        else 
        {     
            auto actorTexture = std::make_shared<sf::Texture>();
            actorTexture->loadFromFile( texName );
            texConnect.insert({texName , actorTexture});
            return actorTexture;
        }
    }
static std::shared_ptr<sf::Texture> loadPassive( const std::string& background )
    { 
        const auto texFind = worldConnect.find( background );
        if( texFind != worldConnect.end())
        {
            return texFind->second; 
        }
        else 
        {     
            auto worldTexture = std::make_shared<sf::Texture>();
            worldTexture->loadFromFile( background );
            worldConnect.insert({background , worldTexture});
            return worldTexture;
        }
    }

static std::shared_ptr<sf::Texture> loadAsset( const std::string& asset )
    { 
        const auto texFind = assetConnect.find( asset );
        if( texFind != assetConnect.end())
        {
            return texFind->second; 
        }
        else 
        {     
            auto assetTexture = std::make_shared<sf::Texture>();
            assetTexture->loadFromFile( asset );
            assetConnect.insert({asset ,  assetTexture});
            return assetTexture;
        }
    }


 static void ErasePrev()
    {
		for( auto t = texConnect.begin(); t != texConnect.end(); )
		{
			if( t->second.unique() )
			{
				t = texConnect.erase( t );
			}
			else
			{
				++t;
			}
		}
    

        for( auto w = worldConnect.begin(); w != worldConnect.end(); )
		{
			if( w->second.unique() )
			{
				w = worldConnect.erase( w );
			}
			else
			{
				++w;
			}
		}
	

    for( auto a = assetConnect.begin(); a != assetConnect.end(); )
		{
			if( a->second.unique() )
			{
				a = assetConnect.erase( a );
			}
			else
			{
				++a;
			}
		}
	}


    