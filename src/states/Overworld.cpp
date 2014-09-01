#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d
#include <GameState.hpp>
#include <Functions.hpp>
#include <Overworld.hpp>
#include <App.hpp>



OverWorld::OverWorld(int prevState, App* app)
{
    // load the background

    // set starting points based on previous state


    // ground shape
    grnd.setPosition(0,app->window_height-20);
    grnd.setSize(sf::Vector2f(app->window_width,20));
    grnd.setFillColor(sf::Color::Cyan);

    // entity shape
    player_pos_x = 100.0;
    player_pos_y = 0.0;
    curPosition = sf::Vector2f(player_pos_x, player_pos_y);
    prevPosition = sf::Vector2f(player_pos_x, player_pos_y);
    entity.setPosition(player_pos_x,player_pos_y);
    entity.setSize(sf::Vector2f(20,40));
    entity.setFillColor(sf::Color::Red);

    //box2d world stuff
    b2Vec2 gravity(0, -9.8); // earth gravity is -9.8
    world = new b2World(gravity); // second bool sleep argument defaults to true in 2.2.1+
    world->SetAutoClearForces(false);
    //world->SetSubStepping(true);

    // box2d ground body stuff
    sf::Vector2f gb_pos = pixels_to_meters(0,-(app->window_height-20));
    groundBodyDef.position.Set(gb_pos.x, gb_pos.y);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    sf::Vector2f gb_scale = pixels_to_meters(app->window_width/2,-1);
    groundBox.SetAsBox(gb_scale.x, gb_scale.y);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // box2d dynamic body
    bodyDef.type = b2_dynamicBody;
    sf::Vector2f db_pos = pixels_to_meters(100,0);
    bodyDef.position.Set(db_pos.x, db_pos.y);
    body = world->CreateBody(&bodyDef);

    sf::Vector2f db_size = pixels_to_meters(20,40);
    dynamicBox.SetAsBox(db_size.x, db_size.y);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f; // bounciness from 0 to 1
    body->CreateFixture(&fixtureDef);

    // box2d timestep values
    timeStep = 1.0f / 60.0f; 
    velocityIterations = 8;
    positionIterations = 3;
}



OverWorld::~OverWorld()
{
    // free resources
    delete world;
}

void OverWorld::pause()
{
    // pause the game
}

void OverWorld::resume()
{
    // pause the game
}

void OverWorld::handle_events(App *app)
{

    //std::cout << "ow handle_events got called" << std::endl;

    sf::Event event;
    while (app->window.pollEvent(event))
    {
        if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            set_next_state(STATE_PAUSE);
            //std::cout << "overworld event loop: setting next state to PAUSE" << std::endl;
        }
        
        if(event.type == sf::Event::Closed)
        {
            std::cout << "Got close window event" << std::endl;
            app->window.close();
        }
        
        if (event.type == sf::Event::Resized)
        {
            app->window_width  = event.size.width;
            app->window_height = event.size.height;
        }

    }
}

void OverWorld::logic(App* app)
{

    
    // get previous player position
    prevPosition = meters_to_pixels(body->GetPosition().x, body->GetPosition().y);
    
    // do physics step
    world->Step(timeStep, velocityIterations, positionIterations);

    // get new player position
    curPosition = meters_to_pixels(body->GetPosition().x, body->GetPosition().y);

    entity.setRotation(body->GetAngle() * (180/3.14159265359));

    // do logic, collision checks, etc

    // move the player etc

    //std::cout << "inside ow logic loop" << std::endl;
}

void OverWorld::render(App *app, double& alpha)
{

    //std::cout << "ow render got called" << std::endl;
    // clear screen and box2d force cache
    world->ClearForces();
    app->window.clear();

    // draw the ground body
    app->window.draw(grnd);

    // get interpolated position
    pos_x = curPosition.x * alpha + prevPosition.x * (1.0f - alpha);
    pos_y = curPosition.y * alpha + prevPosition.y * (1.0f - alpha);

    // position and draw the player
    entity.setPosition(pos_x, -pos_y);
    app->window.draw(entity);
}


