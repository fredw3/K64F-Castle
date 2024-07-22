#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::init(N5110 &lcd, Bitmap &bitmap)
{
    //printf("Player: init called");
    
    _state = 6;
    _health = 6;
    bitmap.render(lcd, 38, 20);
    /*
    init_horiz_coords();
    init_vert_coords();*/
    
    //printf("Player: init ended");
}

void Player::read(Gamepad &pad)
{
    //printf("Player: read called");
    
    read_direction(pad);
    
    //printf("Player: read ended");
}

void Player::update(N5110 &lcd, Bitmap &bitmap, Map &map)
{
    //printf("Player: read called");
    
    update_state();
    
    //printf("_state = %d", _state);
    
    change(lcd, bitmap);
    
    update_coords(map);
    
    //printf("Player: read ended");
}

void Player::set_state(int state)
{
    //printf("Player: set_state called");
    
    _state = state;
    
    //printf("Player: set_state ended");
}

void Player::read_direction(Gamepad &pad)
{
    //printf("Player: read_direction called");
    
    if (pad.get_direction() == N) {
        _stick_input = 0;
    } else if (pad.get_direction() == NE) {
        _stick_input = 1;
    } else if (pad.get_direction() == E) {
        _stick_input = 2;
    } else if (pad.get_direction() == SE) {
        _stick_input = 3;
    } else if (pad.get_direction() == S) {
        _stick_input = 4;
    } else if (pad.get_direction() == SW) {
        _stick_input = 5;
    } else if (pad.get_direction() == W) {
        _stick_input = 6;
    } else if (pad.get_direction() == NW) {
        _stick_input = 7;
    } else if (pad.get_direction() == CENTRE) {
        _stick_input = 8;
    }
    
    //printf("_stick_input = %d", _stick_input);
    
    //printf("Player: read_direction ended");
}

void Player::update_state()
{
    //printf("Player: update_state called");
    
    // State without number represents stationary, with represents moving
    State fsm[12] = {
        //N         NE  E SE  S  SW  W   NW Centred
        /*N*/    {1, 3, 3, 3, 6, 9,  9,  9,  0},
        /*N1*/   {2, 3, 3, 3, 6, 9,  9,  9,  0},
        /*N2*/   {1, 3, 3, 3, 6, 9,  9,  9,  0},
        /*E*/    {0, 4, 4, 4, 6, 9,  9,  9,  3},
        /*E1*/   {0, 5, 5, 5, 6, 9,  9,  9,  3},
        /*E2*/   {0, 4, 4, 4, 6, 9,  9,  9,  3},
        /*S*/    {0, 3, 3, 3, 7, 9,  9,  9,  6},
        /*S1*/   {0, 3, 3, 3, 8, 9,  9,  9,  6},
        /*S2*/   {0, 3, 3, 3, 7, 9,  9,  9,  6},
        /*W*/    {0, 3, 3, 3, 6, 10, 10, 10, 9},
        /*W1*/   {0, 3, 3, 3, 6, 11, 11, 11, 9},
        /*W2*/   {0, 3, 3, 3, 6, 10, 10, 10, 9}
    };

    _state = fsm[_state].next_state[_stick_input];
    
    //printf("_state = %d", _state);
    
    //printf("Player: update_state ended");
}

void Player::change(N5110 &lcd, Bitmap &bitmap)
{
    //printf("Player: change called");
    
    if (_state == 0) {
        Bitmap north_face(north_array, 8, 8);
        north_face.render(lcd, 38, 20);
    } else if (_state == 1) {
        Bitmap north_walk1(north_array1, 8, 8);
        north_walk1.render(lcd, 38, 20);
    } else if (_state == 2) {
        Bitmap north_walk2(north_array2, 8, 8);
        north_walk2.render(lcd, 38, 20);
    } else if (_state == 3) {
        Bitmap east_face(east_array, 8, 8);
        east_face.render(lcd, 38, 20);
    } else if (_state == 4) {
        Bitmap east_walk1(east_array1, 8, 8);
        east_walk1.render(lcd, 38, 20);
    } else if (_state == 5) {
        Bitmap east_walk2(east_array2, 8, 8);
        east_walk2.render(lcd, 38, 20);
    } else if (_state == 6) {
        Bitmap south_face(south_array, 8, 8);
        south_face.render(lcd, 38, 20);
    } else if (_state == 7) {
        Bitmap south_walk1(south_array1, 8, 8);
        south_walk1.render(lcd, 38, 20);
    } else if (_state == 8) {
        Bitmap south_walk2(south_array2, 8, 8);
        south_walk2.render(lcd, 38, 20);
    } else if (_state == 9) {
        Bitmap west_face(west_array, 8, 8);
        west_face.render(lcd, 38, 20);
    } else if (_state == 10) {
        Bitmap west_walk1(west_array1, 8, 8);
        west_walk1.render(lcd, 38, 20);
    } else if (_state == 11) {
        Bitmap west_walk2(west_array2, 8, 8);
        west_walk2.render(lcd, 38, 20);
    }
    
    //printf("Player: change ended");
}

void Player::update_health(int func)
{
    //printf("Player: update_health called");
    
    //printf(_health = %d", _health);
    
    if (func == -1)
    {
        _health -= 1;
        
        //printf(_health = %d", _health);
    }
    else
    {
        _health += 1;
        
        //printf(_health = %d", _health);
    }
    
    //printf("Player: update_health ended");
}

void Player::render_health(N5110 &lcd)
{
    //printf("Player: render_health called");
    
    if (_health == 6)
    {
        health_full(lcd);
        //printf("Player: health_full rendered");
    }
    else if (_health == 5)
    {
        health_five(lcd);
        //printf("Player: health_five rendered");
    }
    else if (_health == 4)
    {
        health_four(lcd);
        //printf("Player: health_four rendered");
    }
    else if (_health == 3)
    {
        health_three(lcd);
        //printf("Player: health_three rendered");
    }
    else if (_health == 2)
    {
        health_two(lcd);
        //printf("Player: health_two rendered");
    }
    else if (_health == 1)
    {
        health_one(lcd);
        //printf("Player: health_one rendered");
    }
    
    //printf("Player: render_health ended");
}

void Player::health_full(N5110 &lcd)
{
    //printf("Player: health_full called");
    
    int i;
    int j = 2;

    for (int y = 0; y <= 5; y++) {
        i = 2;

        for (int x = 0; x <= 21; x++) {
            int pixel = health_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }

        j += 1;
    }
    
    //printf("Player: health_full ended");
}

void Player::health_five(N5110 &lcd)
{
    //printf("Player: health_five called");
    
    int i;
    int j = 2;

    for (int y = 0; y <= 5; y++) {
        i = 2;

        for (int x = 0; x <= 18; x++) {
            int pixel = health_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }

        j += 1;
    }
    
    //printf("Player: health_five ended");
}

void Player::health_four(N5110 &lcd)
{
    //printf("Player: health_four called");
    
    int i;
    int j = 2;

    for (int y = 0; y <= 5; y++) {
        i = 2;

        for (int x = 0; x <= 13; x++) {
            int pixel = health_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }

        j += 1;
    }
    
    //printf("Player: health_four ended");
}

void Player::health_three(N5110 &lcd)
{
    //printf("Player: health_three called");
    
    int i;
    int j = 2;

    for (int y = 0; y <= 5; y++) {
        i = 2;

        for (int x = 0; x <= 10; x++) {
            int pixel = health_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }

        j += 1;
    }
    
    //printf("Player: health_three ended");
}

void Player::health_two(N5110 &lcd)
{
    //printf("Player: health_two called");
    
    int i;
    int j = 2;

    for (int y = 0; y <= 5; y++) {
        i = 2;

        for (int x = 0; x <= 5; x++) {
            int pixel = health_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }

        j += 1;
    }
    
    //printf("Player: health_two ended");
}

void Player::health_one(N5110 &lcd)
{
    //printf("Player: health_one called");
    
    int i;
    int j = 2;

    for (int y = 0; y <= 5; y++) {
        
        i = 2;

        for (int x = 0; x <= 2; x++) {
            int pixel = health_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }

        j += 1;
    }
    
    //printf("Player: health_one ended");
}

void Player::init_horiz_coords() // Top and bottom edges of player array
{
    //printf("Player: init_horiz_coords called");
    
    int y_map = 68; // Initial position (in map) of the top left of the player array

    int x = 0;
    
    int y1 = 0; // Starting and ending subscripts of 'y_coord' to fill
    int y2 = 7;

    while (y_map < 76)
    {
        //printf("y_map = %d", y_map);
        
        for (int x_map = 80; x_map <= 87; x_map++)
        {
            x_coord[x] = x_map;

            x += 1;
            
            //printf("x = %d", x);
        }

        for (int y = y1; y <= y2; y++)
        {
            y_coord[y] = y_map;
        }

        y_map += 7; // Then becomes bottom left of player array
        
        y1 += 8;
        y2 += 8;
    }
    
    //printf("Player: init_horiz_coords ended");
}

void Player::init_vert_coords() // // Left and right edges of player array
{
    //printf("Player: init_vert_coords called");
    
    int x_map = 80; // Initial position (in map) of the subcript just below the top left of the player array

    int y = 16;
    
    int x1 = 16; // Starting and ending subscripts of 'x_coord' to fill
    int x2 = 21;

    while (x_map < 88)
    {
        //printf("x_map = %d", x_map);
        
        for (int y_map = 69; y_map <= 74; y_map++)
        {
            y_coord[y] = y_map;
        
            y += 1;
            
            //printf("y = %d", y);
        }
    
        for (int x = x1; x <= x2; x++)
        {
            x_coord[x] = x_map;
        }

        x_map += 7;
        
        x1 += 6;
        x2 += 6;
    }
    
    //printf("Player: init_vert_coords ended");
}

void Player::update_coords(Map &map)
{
    //printf("Player: update_coords called");
    
    int xshift = map.get_xshift();
    int yshift = map.get_yshift();
    
    // All elements in x_coord array are set in order
    for (int x = 0; x <= 27; x++)
    {
        x_coord[x] += xshift;
    }
    
    for (int y = 0; y <= 27; y++)
    {
        y_coord[y] += yshift;
    }
    
    //printf("Player: update_coords ended");
}

void Player::reset_dmg_collision()
{
    //printf("Player: reset_dmg_collision called");
    
    _dmg_collision = 0;
    
    //printf("Player: reset_dmg_collision ended");
}

void Player::set_dmg_collision(int dmg_collision)
{
    //printf("Player: set_dmg_collision called");
    
    _dmg_collision = dmg_collision;
    
    //printf("Player: set_dmg_collision ended");
}

int Player::get_dmg_collision()
{
    //printf("Player: get_dmg_collision called");
    
    return _dmg_collision;
    
    //printf("Player: get_dmg_collision ended");
}

void Player::set_health(int health)
{
    //printf("Player: set_health called");
    
    _health = health;
    
    //printf("Player: set_health ended");
}

int Player::get_health()
{
    //printf("Player: get_health called");
    
    return _health;
    
    //printf("Player: get_health ended");
}