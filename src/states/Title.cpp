#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d
#include <GameState.hpp>
#include <Title.hpp>


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
