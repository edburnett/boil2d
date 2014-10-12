#ifndef   OVERWORLD_HPP_INCLUDED
#define   OVERWORLD_HPP_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <Functions.hpp>
#include <App.hpp>
#include <Player.hpp>
#include <DebugDraw.hpp>


class OverWorld : public GameState
{
    private:
        // dimensions
        // background

        // SFML shapes
        sf::RectangleShape grnd;

        // box2d things

        b2BodyDef groundBodyDef; // ground body
        b2PolygonShape groundBox; // gound fixture

        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;


    public:
        // load resources, init objects
        OverWorld(int prevState, App* app);
        // free resources
        ~OverWorld();

        // debug draw instance
        DebugDraw debug_draw;
        // create the box2d world
        b2World* world;
        // create the player object
        Player player;

        // main loop functions
        void handle_events(App *app);
        void logic(App* app);
        void pause();
        void resume();
        void render(App *app, double& alpha);
};

#endif
