#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d
#include <GameState.hpp>
#include <Title.hpp>
#include <App.hpp>


Title::Title(App* app)
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
    text.setColor(sf::Color(55,55,55));
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width/2, bounds.height/2);
    text.setPosition((app->window_width - text.getScale().x) / 2, (app->window_height - text.getScale().y) / 4);
}

Title::~Title()
{
    // destruct background, title message
}


void Title::handle_events(App *app)
{
    sf::Event event;
    while (app->window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                app->window.close();
                set_next_state(STATE_EXIT);
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    //std::cout << "title event loop: setting next state to overworld" << std::endl;
                    set_next_state(STATE_OVERWORLD);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    set_next_state(STATE_EXIT);
                    app->window.close();
                }
                break;
            case sf::Event::Resized:
                //app->window_width  = event.size.width;
                //app->window_height = event.size.height;
                break;

        }

    }
}

void Title::logic(App* app)
{

}

void Title::render(App *app, double& alpha)
{
    // show the background
    // show the message
    app->window.clear();
    app->window.draw(text);
}
