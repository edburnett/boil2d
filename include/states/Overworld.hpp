#ifndef   OVERWORLD_HPP_INCLUDED
#define   OVERWORLD_HPP_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <Functions.hpp>
#include <App.hpp>


class OverWorld : public GameState
{
    private:
        // dimensions
        // background

        // SFML shapes
        sf::RectangleShape grnd;
        sf::RectangleShape entity;

        // box2d things

        b2World* world; // box2d world
        b2Body* body;
        b2BodyDef groundBodyDef; // ground body
        b2PolygonShape groundBox; // gound fixture
        b2BodyDef bodyDef; // dynamic body
        b2PolygonShape dynamicBox; // dynamic fixture
        b2FixtureDef fixtureDef;
        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;

        float player_pos_x;
        float player_pos_y;

        // the curerent and previous position/angle/etc of the player goes here?
        sf::Vector2f prevPosition; // in pixels - convert this automagically?
        sf::Vector2f curPosition;  // in pixels - convert this automagically?
        float pos_x;
        float pos_y;




    public:
        // load resources, init objects
        OverWorld(int prevState, App* app);
        // free resources
        ~OverWorld();

        // main loop functions
        void handle_events(App *app);
        void logic(App* app);
        void pause();
        void resume();
        void render(App *app, double& alpha);
};

#endif
