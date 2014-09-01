#ifndef   PAUSE_HPP_INCLUDED
#define   PAUSE_HPP_INCLUDED

// title state
class Pause : public GameState
{
    private:
        // title screen background
        // title screen text/message
        sf::Font font;
        sf::Text pause_title;
        sf::Text pause_menutext;

        sf::RectangleShape pause_bg;

		enum OptionNames
		{
			Play,
			Exit,
		};

		std::vector<sf::Text> menu_options;
		std::size_t	menu_option_index;


    public:
        // loads title screen resources
        Pause(App* app);
        // free resources
        ~Pause();

        // main loop functions
        void handle_events(App* app);
        void logic(App* app);
        void render(App* app, double& alpha);
        void update_option_text();
};

#endif
