#ifndef   TITLE_HPP_INCLUDED
#define   TITLE_HPP_INCLUDED

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
        Title();
        // free resources
        ~Title();

        // main loop functions
        void handle_events(sf::Window &window);
        void logic();
        void render(sf::RenderTarget &window, double& alpha);
};

#endif
