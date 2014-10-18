#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

// boil2d
#include <GameState.hpp>
#include <Pause.hpp>


Pause::Pause(App* app)
{

    if (!title_font.loadFromFile("resource/fonts/LeagueGothic-Regular.otf"))
    {
        std::cout << "Can't load font" << std::endl;
    }

    if (!option_font.loadFromFile("resource/fonts/minecraftia_8.ttf"))
    {
        std::cout << "Can't load font" << std::endl;
    }

    // background
    pause_bg.setPosition(0,0);
    pause_bg.setSize(sf::Vector2f(app->window_width,app->window_height));
    pause_bg.setFillColor(sf::Color(0,0,0,10));

    // title text
    pause_title.setFont(title_font);
    pause_title.setString("PAUSED");
    pause_title.setCharacterSize(200);
    pause_title.setColor(sf::Color(55,55,55));
    sf::FloatRect bounds = pause_title.getLocalBounds();
    pause_title.setOrigin(bounds.width/2, bounds.height/2);
    pause_title.setPosition((app->window_width - pause_title.getScale().x) / 2, (app->window_height - pause_title.getScale().y) / 5);

    // menu options
    sf::Text play_option;
    play_option.setFont(title_font);
    play_option.setString("RESUME");
    play_option.setCharacterSize(16);
    sf::FloatRect po_bounds = play_option.getLocalBounds();
    play_option.setOrigin(po_bounds.width/2.0f, po_bounds.height/2.0f);
    play_option.setPosition((app->window_width - play_option.getScale().x)/2.0f, (app->window_height - play_option.getScale().y)/2.0f);
    play_option.setColor(sf::Color(255,255,255));
    menu_options.push_back(play_option);

    sf::Text exit_option;
    exit_option.setFont(title_font);
    exit_option.setString("EXIT TO MENU");
    exit_option.setCharacterSize(16);
    sf::FloatRect eo_bounds = exit_option.getLocalBounds();
    exit_option.setOrigin(eo_bounds.width/2.0f, eo_bounds.height/2.0f);
    exit_option.setPosition(app->window_width/2.0f, (app->window_height/2.0f)+16);
    exit_option.setColor(sf::Color(155,155,155));
    menu_options.push_back(exit_option);

    menu_option_index = 0;

}

Pause::~Pause()
{
}

void Pause::update_option_text()
{
    if(menu_options.empty())
        return;

    menu_options[menu_option_index].setColor(sf::Color::White); 

}

void Pause::logic(App* app)
{

}

void Pause::render(App* app, double& alpha)
{
    //app->window.clear();
    app->window.draw(pause_bg);
    app->window.draw(pause_title);

	for(auto i = menu_options.begin(); i != menu_options.end(); i++)
    {
		app->window.draw(*i);
    }
}

void Pause::handle_events(App *app)
{
    sf::Event event;
    while (app->window.pollEvent(event))
    {
        if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            set_next_state(STATE_OVERWORLD);
            //std::cout << "unpausing" << std::endl;
        }
        else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
        {
            // TODO this segfaults when UP is pressed first
            if(menu_option_index > 0) {
                menu_option_index--;
            }
            else {
                menu_option_index = menu_options.size() - 1;
                menu_options[menu_option_index-1].setColor(sf::Color(155,155,155));
            }
            update_option_text();
        }
        else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
        {
            if(menu_option_index < menu_options.size() - 1)
            {
                menu_option_index++;
            }
            else
            {
                menu_option_index = 0;
                menu_options[menu_option_index+1].setColor(sf::Color(155,155,155));
            }
            update_option_text();
        }
        
        if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
        {
            if(menu_option_index == Play)
                set_next_state(STATE_OVERWORLD);
            else if(menu_option_index == Exit)
                set_next_state(STATE_TITLE);
                // TODO: clear the state(s) or stack?
        }

        
        if(event.type == sf::Event::Closed)
        {
            app->window.close();
        }
        
        if (event.type == sf::Event::Resized)
        {
            
            //app->window_width  = event.size.width;
            //app->window_height = event.size.height;
            
        }

    }

}
