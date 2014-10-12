#ifndef   App_HPP_INCLUDED
#define   App_HPP_INCLUDED

#include <json/json.h>
#include <SFML/System.hpp>

// App base class
class App
{
    public:
        App();

        // data
        Json::Value config;
        sf::RenderWindow window;
        sf::VideoMode desktop_mode;
        std::vector<sf::VideoMode> video_modes;
        const int WINDOW_WIDTH_DEFAULT  = 940;
        const int WINDOW_HEIGHT_DEFAULT = 540;
        const double TIMESTEP = 1.0f / 60.0f;
        int window_height;
        int window_width;
        int window_bpp;
        bool fullscreen;
        bool debug_draw;
        bool vsync_enabled;

        // methods
        Json::Value get_config();

        // mouse position vector
        sf::Vector2i mouse_position;

        // empty destructor
        ~App(){};
};

#endif
