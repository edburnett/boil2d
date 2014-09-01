#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <App.hpp>
#include <json/json.h>

App::App()
{
    // load config data from file
    config = get_config();

    // get the user's desktop mode
    desktop_mode = sf::VideoMode::getDesktopMode();

    // store window values
    window_height = config["window_height"].asInt();
    window_width  = config["window_width"].asInt();
    if(window_width == 0 || window_height == 0)
    {
        // TODO: handle this?
        throw std::out_of_range("error retrieving config values");
    }

    // create the window
    window.create(sf::VideoMode(window_width, window_height), "Shooter", sf::Style::Resize);
    window.setFramerateLimit(240);


}


Json::Value App::get_config()
{
    bool read_success = false;
    Json::Value config;

    std::ifstream config_file("config.json");
    if(config_file.is_open())
    {
        Json::Reader reader;
        read_success = reader.parse(config_file, config);
        //std::cout << "Config file found" << std::endl;
    }
    else if(!read_success && !config_file.is_open())
    {
        std::cout << "Config file not found, creating new one." << std::endl;

        // add default values
        config["window_width"] = 960;
        config["window_height"] = 540;

        std::ofstream config_file("config.json");

        if(config_file.is_open()) 
        {
            config_file << config;
            config_file.close();
        }

    }
    return config;
}


