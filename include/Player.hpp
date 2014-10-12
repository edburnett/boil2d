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
        
        // sfml sprite representing the player
        sf::Sprite player_shape;
        // dynamic body
        b2Body* player_body;
        b2BodyDef player_bodyDef;
        // dynamic fixture
        b2PolygonShape player_fixture; 
        //b2CircleShape player_fixture;
        b2FixtureDef player_fixtureDef;

        bool move_left = false;
        bool move_right = false;
        bool move_up = false;
        bool move_down = false;
        bool move_stop = false;

        // player texture
        sf::Texture texture;

        // methods
        void set_position();
        void update_angle(sf::Vector2i direction);

        ~Player(){};
};

#endif
