#ifndef   Player_HPP_INCLUDED
#define   Player_HPP_INCLUDED

#include <Box2D/Box2D.h>
#include <Functions.hpp>
#include <Entity.hpp>
#include <App.hpp>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


class Player : public Entity
{
    public:
        Player();

        bool move_left;
        bool move_right;
        bool move_up;
        bool move_down;
        bool move_stop;
        
        // methods
        void set_position();

        ~Player(){};
};

#endif
