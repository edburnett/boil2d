#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <iostream>

// boil2d
#include <Functions.hpp>
#include <Player.hpp>

// Player constructor
Player::Player() 
{

    if (!texture.loadFromFile("resource/sprites/ship.png"))
    {
        std::cout << "player texture load failed" << std::endl;
    }

    // player shape
    float start_pos_x = 100.0;
    float start_pos_y = 0.0;
    cur_position = sf::Vector2f(start_pos_x, start_pos_y);
    prev_position = sf::Vector2f(start_pos_x, start_pos_y);
    player_shape.setTexture(texture);
    //player_shape.setTextureRect(sf::IntRect(0,16,64,48));
    player_shape.setPosition(start_pos_x,start_pos_y);
    // set origin to center TODO turn this sort of thing into a method?
    sf::FloatRect bounds = player_shape.getGlobalBounds();
    player_shape.setOrigin(bounds.width/2, bounds.height/2);
    
    //texture.setSmooth(true);

    // box2d dynamic body
    player_bodyDef.type = b2_dynamicBody;
    sf::Vector2f db_pos = pixels_to_meters(100,0);
    player_bodyDef.position.Set(db_pos.x, db_pos.y);

    //player_fixture.m_p.Set(0,0);
    //player_fixture.m_radius = 0.64; // TODO: this is probably wrong! Calculate it automatically
    sf::Vector2f db_size = pixels_to_meters(32,16); // half-width/half-height for SetAsBox
    player_fixture.SetAsBox(db_size.x, db_size.y);
    player_fixtureDef.shape = &player_fixture;
    player_fixtureDef.density = 1.0f;
    player_fixtureDef.friction = 0.3f;
    player_fixtureDef.restitution = 0.1f; // bounciness from 0 to 1
}


void Player::set_position()
{
}

void Player::update_angle()
{
    player_shape.setRotation(-player_body->GetAngle() * (180/3.14159265359));
}
