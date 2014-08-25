#ifndef   GAMESTATE_HPP_INCLUDED
#define   GAMESTATE_HPP_INCLUDED

#include <SFML/Window.hpp>

// declare GateStates type
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
        virtual void render(sf::RenderTarget &window, double& alpha) = 0;
        virtual ~GameState(){};
};

#endif
