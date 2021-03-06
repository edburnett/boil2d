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

    // get the current and available video mode(s)
    desktop_mode = sf::VideoMode::getDesktopMode();
    video_modes  = sf::VideoMode::getFullscreenModes();

    fullscreen = config.get("fullscreen", false).asBool();
    vsync_enabled = config.get("vsync", false).asBool();
    fps_limit = config.get("fps_limit", 0).asInt();

    // create the window
    if(fullscreen && video_modes[0].isValid())
    {
        std::cout << "setting fullscreen from best mode detected" << std::endl;
        window_width  = video_modes[0].width;
        window_height = video_modes[0].height;
        window_bpp    = video_modes[0].bitsPerPixel;
        window.create(sf::VideoMode(window_width, window_height, window_bpp), "boil2d", sf::Style::Fullscreen);
    }
    else if(fullscreen && !video_modes[0].isValid())
    {
        std::cout << "setting fullscreen from desktop mode" << std::endl;
        window_width  = desktop_mode.width;
        window_height = desktop_mode.height;
        window_bpp    = desktop_mode.bitsPerPixel;
        window.create(sf::VideoMode(desktop_mode), "boil2d", sf::Style::Fullscreen);
    }
    else
    {
        std::cout << "setting from config values" << std::endl;
        window_width  = config.get("window_width", WINDOW_WIDTH_DEFAULT).asInt();
        window_height = config.get("window_height", WINDOW_HEIGHT_DEFAULT).asInt();
        window_bpp    = desktop_mode.bitsPerPixel;
        window.create(sf::VideoMode(window_width, window_height, window_bpp), "boil2d", sf::Style::Resize);
    }

    // set vsync or an fps limit
    if(vsync_enabled)
    {
        // TODO still set frame limit in case vsync fails?
        window.setVerticalSyncEnabled(true);
    }
    else
    {
        if(fps_limit > 0 && fps_limit <= 60)
            // minimum fps limit is 60
            window.setFramerateLimit(60);
        else if(fps_limit > 60)
            window.setFramerateLimit(fps_limit);
    }

    // set initial state of debug_draw
    debug_draw = true;
    dd_textline = 10;
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
        std::cout << "Config file not found, initializing new one." << std::endl;

        // add default values
        config["window_width"]  = WINDOW_WIDTH_DEFAULT;
        config["window_height"] = WINDOW_HEIGHT_DEFAULT;
        config["fullscreen"]    = false;
        config["vsync"]         = false;
        config["fps_limit"]     = 0;

        std::ofstream config_file("config.json");

        if(config_file.is_open()) 
        {
            config_file << config;
            config_file.close();
        }

    }
    return config;
}


