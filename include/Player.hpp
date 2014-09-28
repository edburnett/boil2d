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
            RIGHT,
            UP,
            DOWN,
        };

        move_state movement;

        // player texture
        sf::Texture texture;

        // methods
        void set_position();
        void update_angle();

        ~Player(){};
};

#endif
