#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <math.h>

// boil2d
#include <GameState.hpp>
#include <Functions.hpp>
#include <Overworld.hpp>
#include <App.hpp>
#include <Player.hpp>
#include <DebugDraw.hpp>



OverWorld::OverWorld(int prevState, App* app)
{

    // load the background

    // set starting points based on previous state


    // ground shape
    grnd.setPosition(0,app->window_height-20);
    grnd.setSize(sf::Vector2f(app->window_width,20));
    grnd.setFillColor(sf::Color(76,67,53,128));

    //box2d world stuff
    //b2Vec2 gravity(0, -9.8); // earth gravity is -9.8
    b2Vec2 gravity(0, 0); // earth gravity is -9.8
    world = new b2World(gravity); // second bool sleep argument defaults to true in 2.2.1+
    world->SetAutoClearForces(false);

    // box2d ground body stuff
    sf::Vector2f gb_pos = pixels_to_meters(0,-(app->window_height-20));
    groundBodyDef.position.Set(gb_pos.x, gb_pos.y);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    sf::Vector2f gb_scale = pixels_to_meters(app->window_width,-1);
    groundBox.SetAsBox(gb_scale.x, gb_scale.y);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // add player to box2d world
    player.body = world->CreateBody(&player.body_def);
    player.body->CreateFixture(&player.fixture_def);

    // debug draw
    debug_draw.LinkTarget(app->window);
    debug_draw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit | b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_pairBit);
    world->SetDebugDraw(&debug_draw);

    // box2d timestep values
    velocityIterations = 8;
    positionIterations = 4;

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
            // this fucks up the object/window scaling
            //app->window_width  = event.size.width;
            //app->window_height = event.size.height;
        }

        // toggle debug draw
        if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F1))
        {
            switch(app->debug_draw) 
            {
                case false:
                    app->debug_draw = true;
                    break;
                case true:
                    app->debug_draw = false;
                    break;
            }
                    

        }

    } // event loop

    // reset movement bools to false
    player.move_right = false;
    player.move_left = false;
    player.move_up = false;
    player.move_down = false;
    player.move_stop = false;
    // player movement real-time key presses
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player.move_right = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player.move_left = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player.move_up = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.move_down = true;
    if(!player.move_right && !player.move_left && !player.move_up && !player.move_down)
        player.move_stop = true;
}

void OverWorld::logic(App* app)
{
    // store previous player position
    //player.prev_position = meters_to_pixels(player.player_body->GetPosition().x, player.player_body->GetPosition().y);
    player.prev_position = player.cur_position;

    // do player movement
    player.set_position();

    // do rotation
    app->mouse_position = sf::Mouse::getPosition(app->window);
    player.rotate_to_coords(app->mouse_position);

    // do physics step
    world->Step(app->TIMESTEP, velocityIterations, positionIterations);

    // store new player position
    player.cur_position = meters_to_pixels(player.body->GetPosition().x, player.body->GetPosition().y);

}

void OverWorld::render(App *app, double& alpha)
{
    // clear screen and box2d force cache
    app->window.clear();
    world->ClearForces();

    // draw the ground body
    app->window.draw(grnd);

    // get player interpolated position
    float pos_x = (player.cur_position.x * alpha) + (player.prev_position.x * (1.0f - alpha));
    float pos_y = (player.cur_position.y * alpha) + (player.prev_position.y * (1.0f - alpha));

    // position the player shape
    player.sprite.setPosition(pos_x, -pos_y);

    // debug draw if option enabled
    if(app->debug_draw)
    {
        debug_draw.DrawString(10,app->dd_textline,"FPS: " + std::to_string(app->fps));
        world->DrawDebugData();
    }

    // draw the player sprite to the window
    app->window.draw(player.sprite);
}
