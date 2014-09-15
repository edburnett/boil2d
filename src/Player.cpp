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
    //texture.setSmooth(false);
    player_shape.setTexture(texture);
    player_shape.setPosition(start_pos_x,start_pos_y);
    //player_shape.setColor(sf::Color(255,255,255,200));
    //player_shape.setSize(sf::Vector2f(64,64));
    //player_shape.setFillColor(sf::Color::Red);
    player_shape.setScale(sf::Vector2f(1.0f,1.0f));


    // box2d dynamic body
    player_bodyDef.type = b2_dynamicBody;
    sf::Vector2f db_pos = pixels_to_meters(100,0);
    player_bodyDef.position.Set(db_pos.x, db_pos.y);

    //sf::Vector2f db_size = pixels_to_meters(20,40);
    //sf::Vector2f db_size = pixels_to_meters(64,64);
    //player_fixture.SetAsBox(db_size.x, db_size.y);
    player_fixture.m_p.Set(0,0);
    player_fixture.m_radius = 1; // TODO: this is probably wrong!
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
    player_shape.setRotation(player_body->GetAngle() * (180/3.14159265359));
}
