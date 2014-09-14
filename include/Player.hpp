#ifndef   Player_HPP_INCLUDED
#define   Player_HPP_INCLUDED


#include <Box2D/Box2D.h>
#include <Functions.hpp>
#include <Entity.hpp>
#include <App.hpp>


class Player : public Entity
{
    public:
        Player();
        
        // sfml box/rectable representing the player
        sf::RectangleShape player_shape;
        // dynamic body
        b2Body* player_body;
        b2BodyDef player_bodyDef;
        // dynamic fixture
        b2PolygonShape player_fixture; 
        b2FixtureDef player_fixtureDef;
        b2PolygonShape player_dynamicBox;

        // player's position in pixels
        sf::Vector2f prevPosition;
        sf::Vector2f curPosition;

        // methods
        void set_position();
        void update_angle();

        ~Player(){};
};

#endif
