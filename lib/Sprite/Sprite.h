#ifndef SPRITE_H
#define SPRITE_H

#include "mbed.h"

/** Sprite Class
@brief Library with functions for the sprite array in the game 'Castle'.

@author Frederick Whaley
@date 1st May 2017
*/

class Sprite
{

public:

    Sprite();
    ~Sprite();
    
    /** Initialise
    *
    *   Calls the other two functions.
    */
    void init();
    
    /** Initialise Horizontal Coordinates
    *
    *   Sets the first 16 elements of 'x_coord' and 'y_coord' arrays to the top and bottom 8 subscripts of the sprite on 'map_array' respectively.
    */
    void init_horiz_coords();
    
    /** Initialise Vertical Coordinates
    *
    *   Sets the lasts 12 elements of 'x_coord' and 'y_coord' arrays to the leftmost and rightmost 6 subscripts of the sprite on 'map_array' respectively.
    */
    void init_vert_coords();
    
    int x_coord[28];
    int y_coord[28];

private:

};

static const int sprite_array[8][8] =
{
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

#endif