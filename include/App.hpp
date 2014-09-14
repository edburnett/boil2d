#ifndef   App_HPP_INCLUDED
#define   App_HPP_INCLUDED

#include <json/json.h>

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
        int window_height;
        int window_width;
        int window_bpp;
        bool fullscreen;

        // methods
        Json::Value get_config();

        // empty destructor
        ~App(){};
};

#endif
