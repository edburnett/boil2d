#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <string>


sf::Vector2f meters_to_pixels(float xMeters, float yMeters)
{
    // assumes conversion rate of 50 pixels per meter
    return sf::Vector2f(50.0f * xMeters, 50.0f * yMeters);
}

sf::Vector2f pixels_to_meters(float xPixels, float yPixels)
{
    // assumes conversion rate of 50 pixels per meter
    return sf::Vector2f(0.02f * xPixels, 0.02f * yPixels);
}

enum GameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_OVERWORLD,
    STATE_EXIT,
};

// game state base class
class GameState
{
    public:
        virtual void handle_events(sf::Window &window) = 0;
        virtual void logic() = 0;
        virtual void render(sf::RenderTarget &window, float& interpolation) = 0;
        virtual ~GameState(){};
};

// state status manager
void set_next_state(int newState);

// state changer
void change_state();

// state variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

// game state object
GameState *currentState = NULL;

bool load_files()
{

    // load image
    // do error check

    // load font(s)
    // do error check

    return true;

}

// title state
class Title : public GameState
{
    private:
        // title screen background
        // title screen text/message
        sf::Font font;
        sf::Text text;

    public:
        // loads title screen resources
        Title();
        // free resources
        ~Title();

        // main loop functions
        void handle_events(sf::Window &window);
        void logic();
        void render(sf::RenderTarget &window, float& interpolation);
};

Title::Title()
{
    // load the background

    // setup/render the intro message
    if (!font.loadFromFile("LeagueGothic-Regular.otf"))
    {
        std::cout << "Can't load font" << std::endl;
    }

    // setup text
    //sf::Text text;
    text.setFont(font);
    text.setString("HELL AND EARTH");
    text.setCharacterSize(100);
    text.setColor(sf::Color::White);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width/2, bounds.height/2);
    text.setPosition((800 - text.getScale().x) / 2, (420 - text.getScale().y) / 2 - 100);
}

Title::~Title()
{
    // destruct background, title message
}

void Title::handle_events(sf::Window &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                set_next_state(STATE_EXIT);
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    set_next_state(STATE_OVERWORLD);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    set_next_state(STATE_EXIT);
                    window.close();
                }
                break;
        }


    }
}

void Title::logic()
{

}

void Title::render(sf::RenderTarget &window, float& interpolation)
{
    // show the background
    // show the message
    window.clear();
    window.draw(text);
}

class OverWorld : public GameState
{
    private:
        // dimensions
        // background

        // SFML shapes
        sf::RectangleShape grnd;
        sf::RectangleShape entity;

        // box2d things

        b2World* world; // box2d world
        b2Body* body;
        b2BodyDef groundBodyDef; // ground body
        b2PolygonShape groundBox; // gound fixture
        b2BodyDef bodyDef; // dynamic body
        b2PolygonShape dynamicBox; // dynamic fixture
        b2FixtureDef fixtureDef;
        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;

        float player_pos_x;
        float player_pos_y;    
        float player_vel_x;
        float player_vel_y;


    public:
        // load resources, init objects
        OverWorld(int prevState);
        // free resources
        ~OverWorld();

        // main loop functions
        void handle_events(sf::Window &window);
        void logic();
        void render(sf::RenderTarget &window, float& interpolation);
};

OverWorld::OverWorld(int prevState)
{
    // load the background

    // set starting points based on previous state


    // ground shape
    grnd.setSize(sf::Vector2f(800,20));
    grnd.setPosition(0,400);
    grnd.setFillColor(sf::Color::Cyan);

    // entity shape
    player_pos_x = 100.0f;
    player_pos_y = 0.0f;
    entity.setPosition(player_pos_x,player_pos_y);
    entity.setSize(sf::Vector2f(20,40));
    entity.setFillColor(sf::Color::Red);

    //box2d world stuff
    b2Vec2 gravity(0, -9.8); // earth gravity is -9.8
    world = new b2World(gravity); // second bool sleep argument defaults to true in 2.2.1+
    world->SetAutoClearForces(false);
    //world->SetSubStepping(true);

    // box2d ground body stuff
    sf::Vector2f gb_pos = pixels_to_meters(0,-400);
    groundBodyDef.position.Set(gb_pos.x, gb_pos.y);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    sf::Vector2f gb_scale = pixels_to_meters(400,-1);
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

void OverWorld::handle_events(sf::Window &window)
{

    sf::Event event;
    while (window.pollEvent(event))
    {
        // handle events for the player

        // handle other events
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                set_next_state(STATE_EXIT);
                break;
        }

        // handle quit event
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            set_next_state(STATE_TITLE);
            //window.close();
        }
    }
}

void OverWorld::logic()
{

    // box2d updates
    world->Step(timeStep, velocityIterations, positionIterations);

    // entity updates
    //entity.setRotation(body->GetAngle() * (180/3.14159265359));
    sf::Vector2f body_pos = meters_to_pixels(body->GetPosition().x, -body->GetPosition().y);
    //entity.setPosition(body_pos.x, body_pos.y);
    //player_pos_x = body->GetPosition().x;
    //player_pos_y = body->GetPosition().y;
    player_pos_x = body_pos.x;
    player_pos_y = body_pos.y;

    //b2Vec2 vel = body->GetLinearVelocity();
    //sf::Vector2f body_vel = meters_to_pixels(vel.x, -vel.y);
    //player_vel_x = body_vel.x;
    //player_vel_y = body_vel.y;


    // do logic, collision checks, etc

    // move the player etc
}

void OverWorld::render(sf::RenderTarget& window, float& interpolation)
{

    world->ClearForces();
    // render bg, objects, player, etc
    window.clear();

    window.draw(grnd);

    //entity.setPosition(player_pos_x + (player_vel_x * interpolation), player_pos_y + (player_vel_y * interpolation));
    // TODO try interpolating again except using the prev position instead of the new one?
    // TODO try fix your timestep style instead of dewitters?
    entity.setPosition(player_pos_x, player_pos_y);
    window.draw(entity);
}
        

void set_next_state(int newState)
{
    if(nextState != STATE_EXIT)
    {
        nextState = newState;
    }
}

void change_state()
{
    if(nextState != STATE_NULL)
    {
        // delete current state
        if(nextState != STATE_EXIT)
            delete currentState;

        // change the state
        switch(nextState)
        {
            //delete currentState; // TODO: should we clear out old states when switching?
            case STATE_TITLE:
                currentState = new Title();
                break;

            case STATE_OVERWORLD:
                currentState = new OverWorld(stateID);
                break;
        }

        // change state ID
        stateID = nextState;

        // nullify next state ID
        nextState = STATE_NULL;
    }
}

void clean_up()
{
    // do cleanup
    delete currentState;
}

int main()
{
    // init, load files, etc
    sf::RenderWindow window(sf::VideoMode(800,420), "LD30", 32);
    window.setFramerateLimit(240);
    window.setVerticalSyncEnabled(false);

    // 60 updates per second - minimum recommended for box2d
    const float mUpdateRate = (1000000.0f / 60.0f); // increasing this makes things smoother
    // max updates
    const int mMaxUpdates = 5;
    // Count the number of sequential UpdateFixed loop calls
    sf::Uint32 anUpdates;
    // Clock used in restricting Update loop to a fixed rate
    sf::Clock anUpdateClock;
    // Clock used in calculating the time elapsed since the last frame
    sf::Clock anFrameClock;
    // Restart/Reset our Update clock
    //anUpdateClock.restart();
    // When do we need to update next (in milliseconds)?
    sf::Int32 anUpdateNext = anUpdateClock.getElapsedTime().asMicroseconds();
    float interpolation = 0.0;

    // get a clock for calculating fps
    sf::Clock fps_clock;
    double lasttime = 0;

    // set initial state
    stateID = STATE_TITLE;
    currentState = new Title();


    // main loop here
    while(stateID != STATE_EXIT)
    {
        // make note of the current update time
        sf::Int32 anUpdateTime = anUpdateClock.getElapsedTime().asMicroseconds();

        // handle events
        currentState->handle_events(window);

        // handle logic
        anUpdates = 0;
        while((anUpdateTime - anUpdateNext) >= mUpdateRate && anUpdates++ < mMaxUpdates)
        {
            // update state logic
            currentState->logic(); // moving this outside the loop makes it smooth - why?

            // increment the fixed time step bullshit
            anUpdateNext += mUpdateRate;
        }


        //currentState->logic(); // moving this outside the loop makes it smooth - why?

        // get value for interpolation
        interpolation = float(anUpdateTime + mMaxUpdates - anUpdateNext) / float(mMaxUpdates);

        // change state if needed
        change_state();

        // render the state
        currentState->render(window, interpolation);

        // update screen
        window.display();

        /*
        // calculate FPS for output
        double fps_time = fps_clock.restart().asSeconds();
        double fps = 1.f / (fps_time - lasttime);
        std::cout << "fps: " << fps << "  anUpdateNext: " << anUpdateNext << "  anUpdates: " << anUpdates << "  interpolation: " << interpolation << std::endl;
        */

    }
    // do cleanup
    clean_up();
}
