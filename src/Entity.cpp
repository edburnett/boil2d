#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

// boil2d
#include <Functions.hpp>
#include <Entity.hpp>

// Player constructor
Entity::Entity() 
{


}

void Entity::rotate_to_coords(sf::Vector2i coords)
{
    float shape_angle = body->GetAngle();

    // TODO refactor, clean this up, break up into generic reusable functions, 
    // get rid of magic numbers, etc. Think of multiple use cases for an
    // engine. Code for rotating/facing a mouse pointer code could also be used 
    // to 'lock' on to a target, ala Hotline Miami. Make sure we're not duplicating
    // data saved elsewhere (stored position etc).

    // get sprite position
    sf::Vector2f sprite_position = sprite.getPosition();

    // map to view coords?
    //app->mouse_position = sf::Vector2i(app->window.mapPixelToCoords(app->mouse_position));

    // convert to coords relative to sprite instead of window
    float x = coords.x - sprite_position.x;
    float y = coords.y - sprite_position.y;

    b2Vec2 point = b2Vec2(x,-y);
    b2Vec2 target = point - body->GetPosition();
    float desired_angle = atan2f(-target.x, target.y);
    float nextAngle = shape_angle + body->GetAngularVelocity() / 60;
    float totalRotation = desired_angle - nextAngle;
    while(totalRotation < -180 * DEGTORAD) totalRotation += 360 * DEGTORAD;
    while(totalRotation >  180 * DEGTORAD) totalRotation -= 360 * DEGTORAD;
    float desiredAngularVelocity = totalRotation * 60;
    float impulse = body->GetInertia() * desiredAngularVelocity;

    // apply rotational impulse
    body->ApplyAngularImpulse(impulse, true);

    // update sprite rotation
    sprite.setRotation(-body->GetAngle() * RADTODEG);
}
