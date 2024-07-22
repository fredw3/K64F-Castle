#ifndef MAP_H
#define MAP_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** Map Class
@brief Library with functions for the array used as the map in the game.

@author Frederick Whaley
@date 24th March 2017
*/

class Map
{

public:

    Map();
    ~Map();

    /** Initialise
    *
    *   Calls 'set_keys_zero' function and then calls all functions necessary for drawing and rendering the initial map.
    *   @param lcd - The Nokia N5110 object.
    */
    void init(N5110 &lcd);
    
    /** Read
    *
    *   Calls all functions involved in checking movement of the map in relation to the lcd (player).
    *   @param lcd - The Nokia N5110 object.
    *   @param pad - The Gamepad object.
    */
    void read(N5110 &lcd, Gamepad &pad);
    
    /** Update
    *
    *   Renders the initial subscripts of 'map_array', plus the amount of subscripts in any direction the map has shifted, onto the N5110 screen.
    *   @param lcd - The Nokia N5110 object.
    */
    void update(N5110 &lcd);

    /** Initial Render
    *
    *   Renders the initial subscripts of 'map_array' onto the N5110 screen.
    *   @param lcd - The Nokia N5110 object.
    */
    void init_render(N5110 &lcd);
    
    /** Collision Side Check
    *
    *   Detects whether any pixels adjacent to the Player are set and if so adds 1 to the corresponding integer.
    *   @param lcd - The Nokia N5110 object.
    */
    void collision_side_check(N5110 &lcd);

    /** Collision Corner Check
    *
    *   Detects whether any of the four pixels diagonally adjacent to the Player are set and if so adds 1 to the corresponding integer.
    *   @param lcd - The Nokia N5110 object.
    */
    void collision_corner_check(N5110 &lcd);
    
    /** Set Right Count
    *
    *   Adds or subtracts 1 to the '_right_count' integer depending on whether the player is moving right or left respectively.
    *   A combination of Gamepad direction and collision conditions determines whether each is allowed.
    *   @param pad - The Gamepad object.
    */
    void set_rightcount(Gamepad &pad);

    /** Set Down Count
    *
    *   Adds or subtracts 1 to the '_down_count' integer depending on whether the player is moving down or up respectively.
    *   A combination of Gamepad direction and collision conditions determines whether each is allowed.
    *   @param pad - The Gamepad object.
    */
    void set_downcount(Gamepad &pad);

    /** Set Corner Counts
    *
    *   Adds 1 to either '_upleft_count', '_upright_count', '_downleft_count' or '_downright_count' depending on conditions.
    *   A combination of Gamepad direction and collision conditions determines the conditions.
    *   @param pad - The Gamepad object.
    */
    void set_corner_counts(Gamepad &pad);

    /** Calculate Shift
    *
    *   Calculates the amount the map has shifted on each axis.
    */
    void calc_shift();
    
    /** Get X Shift
    *
    *   Returns '_xshift' integer on the Map object.
    */
    int get_xshift();
    
    /** Get Y Shift
    *
    *   Returns '_yshift' integer on the Map object.
    */
    int get_yshift();

    /** Set Keys to 0
    *
    *   Simply makes sure all the key integers on the map object are set to 0.
    */
    void set_keys_zero();

    /** Fill Top Boundary of Map
    *
    *   Sets the relevant elements in 'map_array' to generate the top line.
    */
    void fill_top();
    
    /** Fill Bottom Boundary of Map
    *
    *   Sets the relevant elements in 'map_array' to generate the bottom line.
    */
    void fill_btm();
    
    /** Fill Left Boundary of Map
    *
    *   Sets the relevant elements in 'map_array' to generate the outer left line.
    */
    void fill_left();
    
    /** Fill Right Boundary of Map
    *
    *   Sets the relevant elements in 'map_array' to generate the outer right line.
    */
    void fill_right();
    
    /** Fill Map Door
    *
    *   Sets the relevant elements in 'map_array' to generate the door.
    */
    void fill_door();
    
    /** Fill Map Rock
    *
    *   Sets the relevant elements in 'map_array' to generate the rock.
    */
    void fill_rock();
    
    /** Fill Map Walls
    *
    *   Sets the relevant elements in 'map_array' to generate the inner walls.
    */
    void fill_walls();
    
    /** Fill Test Sprite
    *
    *   Sets the relevant elements in 'map_array' to generate the 'test sprite' (black 8x8 square) in the 2nd room.
    */
    void fill_sprite();
    
    /** Fill Map Rubble
    *
    *   Sets the relevant elements in 'map_array' to generate pieces of 'rubble'.
    */
    void fill_rubble();

    /** First Key Check
    *
    *   Checks whether the player is adjacent to the rock and if so makes the integer '_first_room_key' = 1.
    *   Also flashes a message to the player (with a wait function) letting them know they've found a key.
    *   Needs to be used in conjunction with a button press on the Gamepad object to work properly (see Engine.cpp).
    *   @param lcd - The Nokia N5110 object.
    */
    void first_key_check(N5110 &lcd);
    
    /** First Door Check
    *
    *   Checks whether the player is adjacent to the door and if so removes it from 'map_array'.
    *   Needs to be used in conjunction with a button press on the Gamepad object to work properly (see Engine.cpp).
    */
    void first_door_check();

    int map_array[144][168];

private:

    int _first_room_key;
    
    int _xshift;
    int _yshift;
    
    int _rightcount;
    int _downcount;
    int _upleft_count;
    int _upright_count;
    int _downleft_count;
    int _downright_count;
    
    int _top_collision;
    int _btm_collision;
    int _left_collision;
    int _right_collision;
    int _top_left_collision;
    int _top_right_collision;
    int _btm_left_collision;
    int _btm_right_collision;

};

#endif