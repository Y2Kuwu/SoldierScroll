// #ifndef TEX_H
// #define TEX_H
// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
// #include <unordered_map>
// #include <vector>
// #include <string>
// #include <memory>
// #include <chrono>



  
//             //returning shared_ptr
//     //static std::shared_ptr<sf::Texture> Tex::loadActor( const std::string& name );
//     //static std::shared_ptr<sf::Texture> Tex::loadPassive( const std::string& background );
//     //static std::shared_ptr<sf::Texture> Tex::loadAsset( const std::string& asset );
//     //static void ErasePrev();

    
// class Tex 
// {
//     public:
//     static std::shared_ptr<sf::Texture> LoadActor( const std::string& name )
//     {
//         const auto t = texConnect.find( name );
//         if( t != texConnect.end())
//         {
//             return t->second; 
//         }
//         else 
//         {     
//             auto actorTexture = std::make_shared<sf::Texture>();
//             actorTexture->loadFromFile( name );
//             texConnect.insert({name , actorTexture});
//             return actorTexture;
//         }

//     }
//     static void ErasePrev()
//     {
// 		for( auto t = texConnect.begin(); t != texConnect.end(); )
// 		{
// 			if( t->second.unique() )
// 			{
// 				t = texConnect.erase( t );
// 			}
// 			else
// 			{
// 				++t;
// 			}
//         }
//     }
    


//         //note to keep static out of method definition
//     private:
           
//         static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> texConnect; 
//         // static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> worldConnect; 
//         // static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> assetConnect;  
    
// };
// std::unordered_map<std::string , std::shared_ptr<sf::Texture>> Tex::texConnect; 
// #endif
// // std::unordered_map<std::string , std::shared_ptr<sf::Texture>> Tex::texConnect; 
// //  static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> worldConnect; 
// //  static std::unordered_map<std::string , std::shared_ptr<sf::Texture>> assetConnect;
   



//     //     for( auto w = worldConnect.begin(); w != worldConnect.end(); )
// 	// 	{
// 	// 		if( w->second.unique() )
// 	// 		{
// 	// 			w = worldConnect.erase( w );
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			++w;
// 	// 		}
// 	// 	}
	

//     // for( auto a = assetConnect.begin(); a != assetConnect.end(); )
// 	// 	{
// 	// 		if( a->second.unique() )
// 	// 		{
// 	// 			a = assetConnect.erase( a );
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			++a;
// 	// 		}
// 	// 	}
// 	// }


