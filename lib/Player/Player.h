#ifndef PLAYER_H
#define PLAYER_H

#include "mbed.h"
#include "Gamepad.h"
#include "Bitmap.h"
#include "N5110.h"
#include "Map.h"

/** Player Class
@brief Library with functions for the player array in the centre of the LCD screen in 'Castle' game.

@author Frederick Whaley
@date 24th March 2017
*/

class Player
{

public:

    Player();
    ~Player();
    
    /** Initialise
    *
    *   Sets starting values for '_state' and '_health' integers on the Player object, and renders the initial array.
    *   @param lcd - The Nokia N5110 object.
    *   @param bitmap - The array used for the character in the centre of the screen.
    */
    void init(N5110 &lcd, Bitmap &bitmap);
    
    /** Read
    *
    *   Calls 'read_direction' function.
    *   @param pad - The Gamepad object.
    */
    void read(Gamepad &pad);
    
    /** Update
    *
    *   Calls 'update_state' function and 'change' functions, rendering the next required player array.
    *   @param lcd - The Nokia N5110 object.
    *   @param bitmap - The array used for the character in the centre of the screen.
    *   @param map - The Map object.
    */
    void update(N5110 &lcd, Bitmap &bitmap, Map &map);
    
    /** Set State
    *
    *   Simple function allowing the user to set the value of '_state'.
    *   @param state - The value to set the integer to.
    */
    void set_state(int state);
    
    /** Read Direction
    *
    *   Sets the private integer '_stick_input' depending on direction read from the joystick on the Gamepad.
    *   From 0 - 8, possible directions are N, NE, E, SE, S, SW, W, NW and centred respectively.
    *   @param pad - The Gamepad object.
    */
    void read_direction(Gamepad &pad);
    
    /** Update State
    *
    *   Initialises a struct 'fsm' of type 'State' (declared in header); each element in the struct contains an integer array.
    *   Each element in the struct represents a Player state and each element in each integer array represents the next state.
    *   Current state ('_state' integer) is then set to the integer in the 'next_state' array corresponding to the subscript number output by '_stick_input'.
    */
    void update_state();
    
    /** Change
    *
    *   Reads '_state' integer and renders the corresponding player array to make the character face the right way.
    *   @param lcd - The Nokia N5110 object.
    *   @param bitmap - The array used for the character in the centre of the screen.
    */
    void change(N5110 &lcd, Bitmap &bitmap);
    
    /** Full Health
    *
    *   Renders the full health array onto the top left of the Nokia N5110 screen to indicate the player has full health.
    *   @param lcd - The Nokia N5110 object.
    */
    void health_full(N5110 &lcd);
    
    /** Five Health
    *
    *   Renders 5/6 of the health array onto the top left of the Nokia N5110 screen to indicate the player has 2 and half hearts of health.
    *   @param lcd - The Nokia N5110 object.
    */
    void health_five(N5110 &lcd);
    
    /** Four Health
    *
    *   Renders 2/3 of the health array onto the top left of the Nokia N5110 screen to indicate the player has 2 hearts of health.
    *   @param lcd - The Nokia N5110 object.
    */
    void health_four(N5110 &lcd);
    
    /** Three Health
    *
    *   Renders 1/2 of the health array onto the top left of the Nokia N5110 screen to indicate the player has 1 and a half hearts of health.
    *   @param lcd - The Nokia N5110 object.
    */
    void health_three(N5110 &lcd);
    
    /** Two Health
    *
    *   Renders 1/3 of the health array onto the top left of the Nokia N5110 screen to indicate the player has 1 heart of health.
    *   @param lcd - The Nokia N5110 object.
    */
    void health_two(N5110 &lcd);
    
    /** One Health
    *
    *   Renders 1/6 of the health array onto the top left of the Nokia N5110 screen to indicate the player has half a heart of health.
    *   @param lcd - The Nokia N5110 object.
    */
    void health_one(N5110 &lcd);
    
    /** Initialise Horizontal Coordinates
    *
    *   Sets the first 16 elements of integer arrays 'x_coord' and 'y_coord' to the subscripts of 'map_array' that are initially in line with the top and bottom 8 elements of the player array respectively.
    */
    void init_horiz_coords();
    
    /** Initialise Vertical Coordinates
    *
    *   Sets the last 12 elements of integer arrays 'x_coord' and 'y_coord' to the subscripts of 'map_array' that are initially in line with the leftmost and rightmost 6 elements of the player array respectively.
    */
    void init_vert_coords();
    
    /** Update Coordinates
    *
    *   Adds the current value of '_xshift' and '_yshift' to all integers in the 'x_coord' and 'y_coord' arrays.
    *   @param map - The Map object.
    */
    void update_coords(Map &map);
    
    /** Reset dmg_collision
    *
    *   Simply sets the value of the '_dmg_collision' integer to 0.
    */
    void reset_dmg_collision();
    
    /** Set dmg_collision
    *
    *   Simply sets the value of the '_dmg_collision' integer.
    *   @param dmg_collision - Number to set it to.
    */
    void set_dmg_collision(int dmg_collision);
    
    /** Get dmg_collision
    *
    *   Simply returns the value of the '_dmg_collision' integer.
    */
    int get_dmg_collision();
    
    /** Update Health
    *
    *   Adds or subtracts 1 from '_health' depending on argument value.
    *   @param func - The control integer (-1 is subtraction, any other values are addition).
    */
    void update_health(int func);
    
    /** Render Health
    *
    *   Reads '_health' integer and renders the corresponding fraction of health_array onto the top left of the LCD screen.
    *   @param lcd - The Nokia N5110 object.
    */
    void render_health(N5110 &lcd);
    
    /** Set Health
    *
    *   Simply sets the value of the '_health' integer.
    *   @param health - Number to set it to.
    */
    void set_health(int health);
    
    /** Get Health
    *
    *   Simply returns the value of the '_health' integer.
    */
    int get_health();
    
    // X and Y coordinates of outer elements of player array (relative to map)
    int x_coord[28];
    int y_coord[28];

    struct State {
        int next_state[9]; // next state (depending on input 0 = N, 1 = NE, 2 = E, 3 = SE, 4 = S, 5 = SW, 6 = W, 7 = NW, 8 = Centred)
    };

private:
    
    int _state;
    int _stick_input;
    int _dmg_collision;
    int _health;
    int _contact_flag;

};

// Health array
static const int health_array[6][22] = {
    {1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},
    {1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
    {0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0},
    {0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0}
};

//Player arrays
static const int north_array[] = {
    0,0,0,1,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,1,1,1,1,0,0,0,
    1,0,1,1,0,1,0,0,
    0,0,1,1,0,0,1,0,
    0,1,1,1,1,0,0,1,
    0,1,0,0,1,0,0,0
};
static const int south_array[] = {
    0,0,0,0,1,0,0,0,
    0,0,0,0,1,1,0,0,
    0,0,0,0,1,1,0,0,
    0,0,0,1,1,1,1,0,
    0,0,1,0,1,1,0,1,
    0,1,0,0,1,1,0,0,
    1,0,0,1,1,1,1,0,
    0,0,0,1,0,0,1,0
};
static const int east_array[] = {
    0,1,0,0,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,0,1,1,0,0,0,1,
    0,1,1,0,0,0,1,0,
    0,1,1,1,1,1,0,0,
    0,1,1,0,1,0,0,0,
    0,1,1,0,0,0,0,0,
    1,0,0,1,0,0,0,0
};
static const int west_array[] = {
    0,0,0,0,0,0,1,0,
    0,0,0,0,1,1,0,0,
    1,0,0,0,1,1,0,0,
    0,1,0,0,0,1,1,0,
    0,0,1,1,1,1,1,0,
    0,0,0,1,0,1,1,0,
    0,0,0,0,0,1,1,0,
    0,0,0,0,1,0,0,1
};

static const int north_array1[] = {
    0,0,0,1,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,1,1,1,1,0,0,0,
    1,0,1,1,0,1,0,0,
    1,0,1,1,0,0,1,0,
    0,1,1,1,1,0,0,1,
    0,0,0,0,1,0,0,0
};

static const int north_array2[] = {
    0,0,1,0,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,0,1,1,0,0,0,0,
    0,1,1,1,1,0,0,0,
    1,0,1,1,0,1,0,0,
    0,0,1,1,0,0,1,0,
    0,1,1,1,1,0,0,1,
    0,1,0,0,0,0,0,0
};

static const int east_array1[] = {
    0,1,0,0,0,0,0,0,
    0,0,1,1,0,0,0,1,
    0,0,1,1,0,0,1,0,
    0,1,1,0,0,1,0,0,
    1,1,1,1,1,0,0,0,
    0,1,1,0,0,0,0,0,
    1,0,1,0,0,0,0,0,
    1,0,0,1,0,0,0,0
};

static const int east_array2[] = {
    0,1,0,0,0,0,0,0,
    0,0,1,1,0,0,0,1,
    0,0,1,1,0,0,1,0,
    0,1,1,0,0,1,0,0,
    1,1,1,1,1,0,0,0,
    0,1,1,0,0,0,0,0,
    0,0,1,1,0,0,0,0,
    1,0,0,1,0,0,0,0
};

static const int south_array1[] = {
    0,0,0,0,1,0,0,0,
    0,0,0,0,1,1,0,0,
    0,0,0,0,1,1,0,0,
    0,0,0,1,1,1,1,0,
    0,0,1,0,1,1,0,1,
    0,1,0,0,1,1,0,1,
    1,0,0,1,1,1,1,0,
    0,0,0,1,0,0,0,0
};

static const int south_array2[] = {
    0,0,0,0,0,1,0,0,
    0,0,0,0,1,1,0,0,
    0,0,0,0,1,1,0,0,
    0,0,0,1,1,1,1,0,
    0,0,1,0,1,1,0,1,
    0,1,0,0,1,1,0,0,
    1,0,0,1,1,1,1,0,
    0,0,0,0,0,0,1,0
};

static const int west_array1[] = {
    0,0,0,0,0,0,1,0,
    1,0,0,0,1,1,0,0,
    0,1,0,0,1,1,0,0,
    0,0,1,0,0,1,1,0,
    0,0,0,1,1,1,1,1,
    0,0,0,0,0,1,1,0,
    0,0,0,0,0,1,0,1,
    0,0,0,0,1,0,0,1
};

static const int west_array2[] = {
    0,0,0,0,0,0,1,0,
    1,0,0,0,1,1,0,0,
    0,1,0,0,1,1,0,0,
    0,0,1,0,0,1,1,0,
    0,0,0,1,1,1,1,1,
    0,0,0,0,0,1,1,0,
    0,0,0,0,1,1,0,0,
    0,0,0,0,1,0,0,1
};

#endif