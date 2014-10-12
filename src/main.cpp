#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <json/json.h>

// boil2d core
#include <App.hpp>
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
std::unique_ptr<GameState> currentState;
std::unique_ptr<GameState> pausedState;


bool load_files()
{
    // TODO: create and move this to App()?

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

void change_state(App* app)
{
    if(nextState != STATE_NULL)
    {

        if(stateID == STATE_OVERWORLD && nextState == STATE_PAUSE)
        {
            //state_stack.push_back(currentState); // put the current state onto the stack
            // TODO swap with whatever is on the stack vector?
            pausedState.swap(currentState);
        }

        // change the state
        switch(nextState)
        {
            case STATE_TITLE:
                currentState.reset(new Title(app));
                break;

            case STATE_OVERWORLD:
                if(stateID == STATE_PAUSE)
                {
                    currentState.swap(pausedState);
                    //state_stack.pop_back(); // clear the last state from the stack
                }
                else
                {
                    currentState.reset(new OverWorld(stateID, app));
                }
                break;

            case STATE_PAUSE:
                currentState.reset(new Pause(app));
                break;
        }

        // change state ID
        stateID = nextState;

        // nullify next state ID
        nextState = STATE_NULL;

    }
}

void clean_up(App *app)
{
    // do cleanup
    currentState.reset();
    delete app;
}

int main()
{
    // instantiate the app class
    App *app = new App();


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
    currentState.reset(new Title(app));
    pausedState.reset(new Pause(app));

    // init the state stack TODO - just work with the stack directly instead of currentState?
    //std::vector<GameState>& state_stack;



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
        currentState->handle_events(app);

        // fixed timestep update loop
        while ( accumulator >= dt )
        {
            //if (stateID != STATE_PAUSE)
            // do logic for current state
            currentState->logic(app);


            // decrement accumulator
            accumulator -= dt;
        }

        // get the alpha
        alpha = accumulator / dt;

        // change state if needed
        change_state(app);

        // render the state
        currentState->render(app, alpha);

        // update screen
        app->window.display();

        // calculate FPS
        double fps_time = fps_clock.restart().asSeconds();
        double fps = 1.f / (fps_time - lasttime);
        std::cout << "state: " << stateID << "fps: " << fps << "  accumulator: " << accumulator << "  alpha: " << alpha << "  frameTime: " << frameTime << std::endl;
    }
    // do cleanup
    clean_up(app);
}
