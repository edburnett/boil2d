#ifndef   Entity_HPP_INCLUDED
#define   Entity_HPP_INCLUDED

//#include <Box2D/Box2D.h>
//#include <SFML/System.hpp>
#include <Functions.hpp>
#include <App.hpp>

/* Base class for all moveables/entities (characters, items, etc) */ 
class Entity
{
    public:
        Entity();
        ~Entity(){};

        // entity's position in pixels
        sf::Vector2f prev_position;
        sf::Vector2f cur_position;
};

#endif
