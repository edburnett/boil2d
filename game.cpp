#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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
        virtual void render() = 0;
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

    public:
        // loads title screen resources
        Title();
        // free resources
        ~Title();

        // main loop functions
        void handle_events(sf::Window &window);
        void logic();
        void render();
};

Title::Title()
{
    // load the background

    // setup/render the intro message
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
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    set_next_state(STATE_OVERWORLD);
                break;
        }

    }
}

void Title::logic()
{

}

void Title::render()
{
    // show the background
    // show the message
}

class OverWorld : public GameState
{
    //private:
        // dimensions
        // background

    public:
        // load resources, init objects
        OverWorld(int prevState);
        // free resources
        ~OverWorld();

        // main loop functions
        void handle_events(sf::Window &window);
        void logic();
        void render();
};

OverWorld::OverWorld(int prevState)
{
    // load the background

    // set some objects

    // set starting points based on previous state

    std::cout << "loading overworld" << std::endl;
}

OverWorld::~OverWorld()
{
    // free resources
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
                break;
        }
    }
}

void OverWorld::logic()
{
    // do logic, collision checks, etc

    // move the player etc
}

void OverWorld::render()
{
    // render bg, objects, player, etc
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
    sf::RenderWindow window(sf::VideoMode(1024,768), "LD30");
    window.setFramerateLimit(120);

    // 20 updates per second
    sf::Uint32 mUpdateRate = (1000.0f / 30.0f);
    // max updates
    const int mMaxUpdates = 5;
    // Clock used in restricting Update loop to a fixed rate
    sf::Clock anUpdateClock;
    // Clock used in calculating the time elapsed since the last frame
    sf::Clock anFrameClock;
    // Restart/Reset our Update clock
    anUpdateClock.restart();
    // When do we need to update next (in milliseconds)?
    sf::Int32 anUpdateNext = anUpdateClock.getElapsedTime().asMilliseconds();

    // get a clock for calculating fps
    sf::Clock fps_clock;
    double lasttime = 0;

    // set initial state
    stateID = STATE_TITLE;
    currentState = new Title();

    // main loop here
    while(stateID != STATE_EXIT)
    {
        // Count the number of sequential UpdateFixed loop calls
        sf::Uint32 anUpdates = 0;

        // make note of the current update time
        sf::Int32 anUpdateTime = anUpdateClock.getElapsedTime().asMilliseconds();

        // handle events
        currentState->handle_events(window);

        // handle logic
        while((anUpdateTime - anUpdateNext) >= mUpdateRate && anUpdates++ < mMaxUpdates)
        {
            currentState->logic();
            anUpdateNext += mUpdateRate;
        }

        // change state if needed
        change_state();

        // render the state
        currentState->render();

        // update screen
        window.display();

        // calculate FPS
        double fps_time = fps_clock.restart().asSeconds();
        double fps = 1.f / (fps_time - lasttime);
        std::cout << "fps: " << fps << "  anUpdateNext: " << anUpdateNext << "  anUpdates: " << anUpdates << std::endl;

    }
    // do cleanup
    clean_up();
}
