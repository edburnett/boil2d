#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d core
#include <GameState.hpp>
#include <Functions.hpp>

// states
#include <Pause.hpp>
#include <Title.hpp>
#include <Overworld.hpp>


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

    // init the state stack TODO - just store as "previousState" instead of a vector?
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
        std::cout << "fps: " << fps << "  accumulator: " << accumulator << "  alpha: " << alpha << "  frameTime: " << frameTime << std::endl;
    }
    // do cleanup
    clean_up();
}
