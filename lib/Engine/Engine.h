#ifndef ENGINE_H
#define ENGINE_H

#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "Player.h"
#include "Sprite.h"
#include "Map.h"

/** Engine Class
@brief Library containing the main functions used to interact with the game 'Castle'.

@author Frederick Whaley
@date 30th April 2017
*/

class Engine
{

public:

    Engine();
    ~Engine();
    
    /** Initialise
    *
    *   Calls the initialisation functions for the Map and Player objects.
    *   @param lcd - The Nokia N5110 object.
    *   @param bitmap - The array used for the character in the centre of the screen.
    */
    void init(N5110 &lcd, Bitmap &bitmap);
    
    /** Read Game State
    *
    *   Calls the functions involved in reading user input and calculating states for the Map and Player objects.
    *   @param lcd - The Nokia N5110 object.
    *   @param pad - The Gamepad object.
    */
    void read(N5110 &lcd, Gamepad &pad);
    
    /** Update
    *
    *   Starts by calling key and door check code for the Map object and updating accordingly, then calls general update functions for the Map and Player objects.
    *   @param pad - The Gamepad object.
    *   @param lcd - The Nokia N5110 object.
    *   @param bitmap - The array used for the character in the centre of the screen.
    */
    void update(Gamepad &pad, N5110 &lcd, Bitmap &bitmap);
    
    /** Check Damages
    *
    *   Checks whether any of the outer coordinates of the player are adjacent to those of the sprite and if so adds the amount to '_dmg_collision' integer on Player object.
    */
    void check_damages();
    
    /** Damage Occurred
    *
    *   Calls the 'check_damages' function, then returns true if the player is adjacent to the sprite, false if not.
    */
    bool damage_occur();
    
    /** Update Health
    *
    *   Increases or decreases the '_health' integer on the Player by calling the 'update_health' function on the Player object.
    *   Whether '_health' increases or decreases depends on the argument (-1 for subtract, anything else for add).
    *   @param func - The integer used as the control variable.
    */
    void update_health(int func);
    
    /** Render Health
    *
    *   Calls the 'render_health' function on the Player object.
    *   @param lcd - The Nokia N5110 object.
    */
    void render_health(N5110 &lcd);
    
    /** Render Health
    *
    *   Calls the 'get_health' function on the Player object, returning the property from it.
    */
    int get_health();

private:

    Player _player;
    Sprite _sprite;
    Map _map;

};

#endif