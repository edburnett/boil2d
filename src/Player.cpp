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
    // handle player movement
    b2Vec2 vel = player_body->GetLinearVelocity();
    sf::Vector2f desired_vel(0,0);
    if(move_left && !move_right)
    {
        desired_vel.x += b2Max(vel.x - 0.9f, -15.0f);
    }

    if(move_right && !move_left)
    {
        desired_vel.x += b2Min(vel.x + 0.9f, 15.0f);
    }

    if(move_up && !move_down)
    {
        desired_vel.y += b2Min(vel.y + 0.9f, 15.0f);
    }
    if(move_down && !move_up)
    {
        desired_vel.y += b2Max(vel.y - 0.9f, -15.0f);
    }
    if(move_stop)
    {
        // TODO: also do this if opposite keys are pressed? or switch directions? or ignore?
        desired_vel.x += vel.x * 0.82; // <1, smaller value = faster stop
        desired_vel.y += vel.y * 0.82; // <1, smaller value = faster stop
    }

    double vel_change_x = desired_vel.x - vel.x;
    double vel_change_y = desired_vel.y - vel.y;
    double impulse_x = (player_body->GetMass() * vel_change_x);
    double impulse_y = (player_body->GetMass() * vel_change_y);

    // normalize diagonal movement
    if (impulse_x != 0.f && impulse_y != 0.f)
    {
        impulse_x /= std::sqrt(2.f);
        impulse_y /= std::sqrt(2.f);
    }

    //std::cout << impulse_x << impulse_y << std::endl;

    // apply impulse
    player_body->ApplyLinearImpulse(b2Vec2(impulse_x,impulse_y), player_body->GetWorldCenter(), true);

}

void Player::update_angle()
{
    player_shape.setRotation(-player_body->GetAngle() * (180/3.14159265359));
}

