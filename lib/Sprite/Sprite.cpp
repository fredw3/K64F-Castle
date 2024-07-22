#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void Sprite::init()
{
    //printf("Sprite: init called");
    
    init_horiz_coords();
    init_vert_coords();
    
    //printf("Sprite: init ended");
}

void Sprite::init_horiz_coords()
{
    //printf("Sprite: init_horiz_coords called");
    
    int y_map = 75; // Initial y position (in map_array) of the top left of the sprite array

    int x = 0;
    
    int y1 = 0; // Starting and ending subscripts to fill
    int y2 = 7;

    while (y_map < 83)
    {
        //printf("y_map = %d", y_map);
        
        for (int x_map = 53; x_map <= 60; x_map++)
        {
            x_coord[x] = x_map;

            x += 1;
            
            //printf("x = %d", x);
        }

        for (int y = y1; y <= y2; y++)
        {
            y_coord[y] = y_map;
        }

        y_map += 7; // Then becomes bottom left of sprite array
        
        y1 += 8;
        y2 += 8;
    }
    //printf("Sprite: init_horiz_coords ended");
}

void Sprite::init_vert_coords()
{
    //printf("Sprite: init_vert_coords called");
    
    int x_map = 53; // Initial x position (in map_array) of the top left of the sprite array

    int y = 16;
    
    int x1 = 16; // Starting and ending subscripts to fill
    int x2 = 21;

    while (x_map < 61)
    {
        //printf("x_map = %d", x_map);
        
        for (int y_map = 76; y_map <= 81; y_map++)
        {
            y_coord[y] = y_map;
        
            y += 1;
            
            //printf("y = %d", y);
        }
    
        for (int x = x1; x <= x2; x++)
        {
            x_coord[x] = x_map;
        }

        x_map += 7; // Then becomes bottom left of sprite array
        
        x1 += 6;
        x2 += 6;
    }
    
    //printf("Sprite: init_vert_coords ended");
}