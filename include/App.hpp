#ifndef   APP_HPP_INCLUDED
#define   APP_HPP_INCLUDED

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
        int window_height;
        int window_width;
        int stateID;
        int nextState;

        // methods
        Json::Value get_config();



        // empty destructor
        ~App(){};
};

#endif
