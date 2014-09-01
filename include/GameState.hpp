#ifndef   GAMESTATE_HPP_INCLUDED
#define   GAMESTATE_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <vector>
#include <App.hpp>

// state status manager
void set_next_state(int newState);

// declare GateStates type
enum GameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_OVERWORLD,
    STATE_PAUSE,
    STATE_EXIT,
};

// game state base class
class GameState
{
    public:
        virtual void handle_events(App *app) = 0;
        virtual void logic(App* app) = 0;
        virtual void render(App *app, double &alpha) = 0;
        //virtual ~GameState(){};
};

#endif
