#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d
#include <GameState.hpp>
#include <Pause.hpp>


Pause::Pause()
{
    pause_screen.setPosition(0,0);
    pause_screen.setSize(sf::Vector2f(800,420));
    pause_screen.setFillColor(sf::Color(35,35,35,50));
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
