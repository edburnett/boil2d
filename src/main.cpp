#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d core
#include <GameState.hpp>

// states
#include <Title.hpp>
#include <Pause.hpp>
#include <Overworld.hpp>

// this test is inspired a combination of GQE, Lazyfoo State Machine, and 
// gaffer's fixed timestep article


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


Title::Title()
{
    // load the background

    // setup/render the intro message
    if (!font.loadFromFile("resource/fonts/LeagueGothic-Regular.otf"))
    {
        std::cout << "Can't load font" << std::endl;
    }

    // setup text
    //sf::Text text;
    text.setFont(font);
    text.setString("BOIL2D");
    text.setCharacterSize(200);
    text.setColor(sf::Color(35,35,35));
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

void Title::render(sf::RenderTarget &window, double& alpha)
{
    // show the background
    // show the message
    window.clear();
    window.draw(text);
}

Pause::Pause()
{
    pause_screen.setPosition(0,0);
    pause_screen.setSize(sf::Vector2f(800,420));
    pause_screen.setFillColor(sf::Color(255,255,255,32));
}

Pause::~Pause()
{
}

void Pause::logic()
{
}

void Pause::render(sf::RenderTarget &window, double& alpha)
{
    window.draw(pause_screen);
}

void Pause::handle_events(sf::Window &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // handle quit event
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            //set_next_state(STATE_TITLE);
            set_next_state(STATE_OVERWORLD);
            //window.close();
        }
    }

}



OverWorld::OverWorld(int prevState)
{
    // load the background

    // set starting points based on previous state


    // ground shape
    grnd.setPosition(0,400);
    grnd.setSize(sf::Vector2f(800,20));
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

void OverWorld::pause()
{
    // pause the game
}

void OverWorld::resume()
{
    // pause the game
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
            //set_next_state(STATE_TITLE);
            set_next_state(STATE_PAUSE);
            //window.close();
        }
    }
}

void OverWorld::logic()
{

    
    // get previous player position
    prevPosition = meters_to_pixels(body->GetPosition().x, body->GetPosition().y);
    
    // do physics step
    world->Step(timeStep, velocityIterations, positionIterations);

    // get new player position
    curPosition = meters_to_pixels(body->GetPosition().x, body->GetPosition().y);

    //entity.setRotation(body->GetAngle() * (180/3.14159265359));

    // do logic, collision checks, etc

    // move the player etc
}

void OverWorld::render(sf::RenderTarget& window, double& alpha)
{

    // clear screen and box2d force cache
    world->ClearForces();
    window.clear();

    // draw the ground body
    window.draw(grnd);

    // get interpolated position
    pos_x = curPosition.x * alpha + prevPosition.x * (1.0f - alpha);
    pos_y = curPosition.y * alpha + prevPosition.y * (1.0f - alpha);

    // position and draw the player
    entity.setPosition(pos_x, -pos_y);
    window.draw(entity);
}

   

void set_next_state(int newState)
{
    if(nextState != STATE_EXIT)
    {
        nextState = newState;
    }
}

void change_state(std::vector<GameState*>& state_stack)
{
    if(nextState != STATE_NULL)
    {

        if(stateID == STATE_OVERWORLD)
            state_stack.push_back(currentState); // put the current state onto the stack

        // delete current state
        if(nextState != STATE_EXIT && nextState != STATE_PAUSE)
            delete currentState;

        // change the state
        switch(nextState)
        {
            case STATE_TITLE:
                currentState = new Title();
                break;

            case STATE_PAUSE:
                currentState = new Pause();
                break;

            case STATE_OVERWORLD:
                if(stateID == STATE_PAUSE)
                {
                    currentState = state_stack.back();
                    state_stack.pop_back(); // clear the last state from the stack
                }
                else
                {
                    currentState = new OverWorld(stateID);
                }
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

    // gaffer loop time stuff
    sf::Clock clock;

    //double dt = 0.01f;
    double dt = 1.0f / 60.0f; // this is same as timeStep
    double alpha;

    double currentTime = clock.getElapsedTime().asSeconds();
    double accumulator = 0.0f;

    // get a clock for calculating fps
    sf::Clock fps_clock;
    double lasttime = 0;

    // set initial state
    stateID = STATE_TITLE;
    currentState = new Title();

    // init the state stack
    std::vector<GameState*> state_stack;


    // main loop here
    while(stateID != STATE_EXIT)
    {
        double newTime = clock.getElapsedTime().asSeconds();
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25)
            frameTime = 0.25;

        currentTime = newTime;
        accumulator += frameTime;

        // handle events
        currentState->handle_events(window);

        // fixed timestep update loop
        while ( accumulator >= dt )
        {
            if (stateID != STATE_PAUSE)
                // do logic for current state
                currentState->logic();


            // decrement accumulator
            accumulator -= dt;
        }

        // get the alpha
        alpha = accumulator / dt;

        // change state if needed
        change_state(state_stack);

        // render the state
        currentState->render(window, alpha);

        // update screen
        window.display();

        // calculate FPS for output
        double fps_time = fps_clock.restart().asSeconds();
        double fps = 1.f / (fps_time - lasttime);
        //std::cout << "fps: " << fps << "  accumulator: " << accumulator << "  alpha: " << alpha << "  frameTime: " << frameTime << std::endl;

        std::cout << state_stack.size() << std::endl;

    }
    // do cleanup
    clean_up();
}
