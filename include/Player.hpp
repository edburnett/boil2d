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

        enum move_state {
            STOP,
            LEFT,
            LEFT_DOWN,
            LEFT_UP,
            RIGHT,
            RIGHT_DOWN,
            RIGHT_UP,
            UP,
            DOWN,
        };

        bool M_LEFT = false;
        bool M_RIGHT = false;
        bool M_UP = false;
        bool M_DOWN = false;

        move_state movement;

        // player texture
        sf::Texture texture;

        // methods
        void set_position();
        void update_angle();

        ~Player(){};
};

#endif
