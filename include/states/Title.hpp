#ifndef   TITLE_HPP_INCLUDED
#define   TITLE_HPP_INCLUDED

#include <App.hpp>

// title state
class Title : public GameState
{
    private:
        // title screen background
        // title screen text/message
        sf::Font font;
        sf::Text text;

    public:
        // loads title screen resources
        Title(App* app);
        // free resources
        ~Title();

        // main loop functions
        void handle_events(App *app);
        void logic(App* app);
        void render(App *app, double& alpha);
};

#endif
