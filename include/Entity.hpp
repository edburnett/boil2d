#ifndef   Entity_HPP_INCLUDED
#define   Entity_HPP_INCLUDED

//#include <Box2D/Box2D.h>
//#include <SFML/System.hpp>
#include <Functions.hpp>
#include <App.hpp>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


/* Base class for all moveable sprites/entities (characters, items, etc) */ 
class Entity
{
    public:
        Entity();
        ~Entity(){};

        // sfml sprite representing the entity
        sf::Sprite sprite;
        // player texture
        sf::Texture texture;
        // dynamic body
        b2Body* body;
        b2BodyDef body_def;
        // dynamic fixture
        b2PolygonShape fixture; 
        b2FixtureDef fixture_def;

        // entity's coordinates in pixels
        sf::Vector2f prev_position;
        sf::Vector2f cur_position;

        // methods
        void set_position();
        void rotate_to_coords(sf::Vector2i coords);
};

#endif
