#ifndef   PAUSE_HPP_INCLUDED
#define   PAUSE_HPP_INCLUDED

// title state
class Pause : public GameState
{
    private:
        // title screen background
        // title screen text/message
        sf::Font font;
        sf::Text text;

    public:
        // loads title screen resources
        Pause();
        // free resources
        ~Pause();

        // main loop functions
        void handle_events(sf::Window &window);
        void logic();
        void render(sf::RenderTarget &window, double& alpha);
};

#endif
