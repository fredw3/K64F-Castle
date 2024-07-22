#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::init(N5110 &lcd)
{
    //printf("Map: init called");
    
    set_keys_zero();
    fill_top();
    fill_btm();
    fill_left();
    fill_right();
    fill_door();
    fill_rock();
    fill_rubble();
    fill_walls();
    fill_sprite();
    init_render(lcd);
    
    //printf("Map: init ended");
}

void Map::read(N5110 &lcd, Gamepad &pad)
{
    //printf("Map: read called");
    
    collision_side_check(lcd);
    collision_corner_check(lcd);
    set_downcount(pad);
    set_rightcount(pad);
    set_corner_counts(pad);
    calc_shift();
    
    //printf("Map: read ended");
}

void Map::update(N5110 &lcd)
{
    //printf("Map: update called");

    int i;
    int j = 0;

    // Initial y subscripts of 'map_array' rendered
    for (int y = 48; y <= 95; y++)
    {
        i = 0;
        
        // Initial x subscripts of 'map_array' rendered
        for (int x = 42; x <= 125; x++)
        {
            int pixel = map_array[y + _yshift][x + _xshift];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }
        j += 1;
    }
    
    //printf("Map: update ended");
}


void Map::init_render(N5110 &lcd)
{
    //printf("Map: init_render called");
    
    int i;
    int j = 0;

    // Initial y subscripts of 'map_array' rendered
    for (int y = 48; y <= 95; y++)
    {
        i = 0;
        
        // Initial x subscripts of 'map_array' rendered
        for (int x = 42; x <= 125; x++)
        {
            int pixel = map_array[y][x];

            lcd.setPixel(i,j,pixel);

            i += 1;
        }
        j += 1;
    }
    
    //printf("Map: init_render ended");
}

void Map::collision_side_check(N5110 &lcd)
{
    //printf("Map: collision_side_check called");
    
    _top_collision = 0;
    _btm_collision = 0;
    _left_collision = 0;
    _right_collision = 0;

    for (int x = 38; x <= 45; x++) // Top (8)
    {
        if (lcd.getPixel(x,19) == 1)
        {
            _top_collision += 1;
            //printf("_top_collision = %d", _top_collision);
        }
    }
    for (int x = 38; x <= 45; x++) // Bottom (8)
    {
        if (lcd.getPixel(x,28) == 1)
        {
            _btm_collision += 1;
            //printf("_btm_collision = %d", _btm_collision);
        }
    }
    for (int y = 20; y <= 27; y++) // Left (8)
    {
        if (lcd.getPixel(37,y) == 1)
        {
            _left_collision += 1;
            //printf("_left_collision = %d", _left_collision);
        }
    }
    for (int y = 20; y <= 27; y++) // Right (8)
    {
        if (lcd.getPixel(46,y) == 1)
        {
            _right_collision += 1;
            //printf("_right_collision = %d", _right_collision);
        }
    }
    
    //printf("Map: collision_side_check ended");
}

void Map::collision_corner_check(N5110 &lcd)
{
    //printf("Map: collision_corner_check called");
    
    _top_left_collision = 0;
    _top_right_collision = 0;
    _btm_left_collision = 0;
    _btm_right_collision = 0;

    if (lcd.getPixel(37,19) == 1)
    {
        _top_left_collision += 1;
        //printf("_top_left_collision = %d", _top_left_collision);
    }
    if (lcd.getPixel(46,19) == 1)
    {
        _top_right_collision += 1;
        //printf("_top_right_collision = %d", _top_right_collision);
    }
    if (lcd.getPixel(37,28) == 1)
    {
        _btm_left_collision += 1;
        //printf("_btm_left_collision = %d", _btm_left_collision);
    }
    if (lcd.getPixel(46,28) == 1)
    {
        _btm_right_collision += 1;
        //printf("_btm_right_collision = %d", _btm_right_collision);
    }
    //printf("Map: collision_corner_check ended");
}

void Map::set_rightcount(Gamepad &pad)
{
    //printf("Map: set_rightcount called");
    
    if ((pad.get_direction() == E && _right_collision == 0) || (pad.get_direction() == NE && _right_collision == 0 && _top_collision != 0) || (pad.get_direction() == SE && _right_collision == 0 && _btm_collision != 0))
    {
        _rightcount += 1;
        //printf("_rightcount = %d", _rightcount);
    }
    if ((pad.get_direction() == W && _left_collision == 0) || (pad.get_direction() == NW && _left_collision == 0 && _top_collision != 0) || (pad.get_direction() == SW && _left_collision == 0 && _btm_collision != 0))
    {
        _rightcount -= 1;
        //printf("_rightcount = %d", _rightcount);
    }
    //printf("Map: set_rightcount ended");
}

void Map::set_downcount(Gamepad &pad)
{
    //printf("Map: set_downcount called");
    
    if ((pad.get_direction() == S && _btm_collision == 0) || (pad.get_direction() == SW && _btm_collision == 0 && _left_collision != 0) || (pad.get_direction() == SE && _btm_collision == 0 && _right_collision != 0))
    {
        _downcount += 1;
        //printf("_downcount = %d", _downcount);
    } 
    else if ((pad.get_direction() == N && _top_collision == 0) || (pad.get_direction() == NW && _top_collision == 0 && _left_collision != 0) || (pad.get_direction() == NE && _top_collision == 0 && _right_collision != 0))
    {
        _downcount -= 1;
        //printf("_downcount = %d", _downcount);
    }
    //printf("Map: set_downcount ended");
}

void Map::set_corner_counts(Gamepad &pad)
{
    //printf("Map: set_corner_counts called");
    
    if (pad.get_direction() == NW && _top_left_collision == 0 && _top_collision == 0 && _left_collision == 0)
    {
        _upleft_count += 1;
        //printf("_upleft_count = %d", _upleft_count);
    }
    if (pad.get_direction() == NE && _top_right_collision == 0 && _top_collision == 0 && _right_collision == 0)
    {
        _upright_count += 1;
        //printf("_upright_count = %d", _upright_count);
    }
    if (pad.get_direction() == SW && _btm_left_collision == 0 && _btm_collision == 0 && _left_collision == 0)
    {
        _downleft_count += 1;
        //printf("_downleft_count = %d", _downleft_count);
    }
    if (pad.get_direction() == SE && _btm_right_collision == 0 && _btm_collision == 0 && _right_collision == 0)
    {
        _downright_count += 1;
        //printf("_downright_count = %d", _downright_count);
    }
    //printf("Map: set_corner_counts ended");
}

void Map::calc_shift()
{
    //printf("Map: calc_shift called");
    
    _yshift = _downleft_count + _downcount + _downright_count - _upleft_count - _upright_count;
    _xshift = _upright_count + _rightcount + _downright_count - _upleft_count - _downleft_count;
    
    //printf("Map: calc_shift ended");
}

int Map::get_xshift()
{
    //printf("Map: get_xshift called");
    
    return _xshift;
    
    //printf("Map: get_xshift ended");
}

int Map::get_yshift()
{
    //printf("Map: get_yshift called");
    
    return _yshift;
    
    //printf("Map: get_yshift ended");
}

void Map::set_keys_zero()
{
    //printf("Map: set_keys_zero called");
    
    _first_room_key = 0;
    
    //printf("Map: set_keys_zero ended");
}

void Map::fill_top()
{
    //printf("Map: fill_top called");
    
    int y = 28;

    for (int x = 42; x <= 125; x++)
    {
        map_array[y][x] = 1;
    }
    
    //printf("Map: fill_top ended");
}

void Map::fill_btm()
{
    //printf("Map: fill_btm called");
    
    int y = 95;

    for (int x = 42; x <= 125; x++)
    {
        map_array[y][x] = 1;
    }
    
    //printf("Map: fill_btm ended");
}

void Map::fill_left()
{
    //printf("Map: fill_left called");
    
    int x = 42;

    for (int y = 29; y <= 94; y++)
    {
        map_array[y][x] = 1;
    }
    
    //printf("Map: fill_left ended");
}

void Map::fill_right()
{
    //printf("Map: fill_right called");
    
    int x = 125;

    for (int y = 29; y <= 94; y++)
    {
        map_array[y][x] = 1;
    }
    
    //printf("Map: fill_right ended");
}

void Map::fill_rock()
{
    //printf("Map: fill_rock called");
    
    for (int y = 52; y <= 53; y++)
    {
        for (int x = 117; x <= 118; x++)
        {
            map_array[y][x] = 1;
        }
    }
    
    //printf("Map: fill_rock ended");
}

void Map::fill_door()
{
    //printf("Map: fill_door called");
    
    for (int y = 47; y <= 49; y++)
    {
        for (int x = 78; x <= 89; x++)
        {
            map_array[y][x] = 1;
        }
    }
    
    //printf("Map: fill_door ended");
}

void Map::fill_rubble()
{
    //printf("Map: fill_rubble called");
    
    int y = 91;

    for (int x = 110; x <= 112; x++)
    {
        map_array[y][x] = 1;
    }

    map_array[73][122] = map_array[51][102] = map_array[51][103] = map_array[86][74] = map_array[87][74] = map_array[91][73] = map_array[93][75] = map_array[77][118] = map_array[73][122] = 1;
    
    //printf("Map: fill_rubble ended");
}

void Map::fill_walls()
{
    //printf("Map: fill_walls called");
    
    int y = 48;

    for (int x = 43; x <= 50; x++)
    {
        map_array[y][x] = 1;
    }

    for (int x = 63; x <= 77; x++)
    {
        map_array[y][x] = 1;
    }

    for (int x = 90; x <= 124; x++)
    {
        map_array[y][x] = 1;
    }

    int x = 71;

    for (y = 48; y <= 94; y++)
    {
        map_array[y][x] = 1;
    }
    //printf("Map: fill_walls ended");
}

void Map::fill_sprite()
{
    //printf("Map: fill_sprite called");
    
    for (int y = 75; y <= 82; y++)
    {
        for (int x = 53; x <= 60; x++)
        {
            map_array[y][x] = 1;
        }
    }
    //printf("Map: fill_sprite ended");
}

void Map::first_key_check(N5110 &lcd)
{
    //printf("Map: first_key_check called");
    
    // Do nothing if key has already been picked up
    if (_first_room_key == 1) 
    {
    }

    // Player is adjacent to bottom edge of rock which hides key
    else if ((_xshift == 37 || _xshift == 36 || _xshift == 35 || _xshift == 34 || _xshift == 33 || _xshift == 32 || _xshift == 31 || _xshift == 30 || _xshift == 29) && (_yshift == -14))
    {
        _first_room_key = 1;

        lcd.printString("Picked up key!", 2, 5);
        lcd.refresh();
        wait(0.5);
    }

    // Player is adjacent to left edge of rock which hides key
    else if ((_yshift == -19 || _yshift == -18 || _yshift == -17 || _yshift == -16 || _yshift == -15) && (_xshift == 29))
    {
        _first_room_key = 1;

        lcd.printString("Picked up key!", 2, 5);
        lcd.refresh();
        wait(0.5);
    }
    //printf("Map: first_key_check ended");
}

void Map::first_door_check()
{
    //printf("Map: first_door_check called");
    
    // Player is adjacent to bottom of door
    if (_first_room_key == 1 && _yshift == -18 && (_xshift == -8 || _xshift == -7 || _xshift == -6 || _xshift == -5 || _xshift == -4 || _xshift == -3 || _xshift == -2 || _xshift == -1 || _xshift == 0 || _xshift == 1 || _xshift == 2 || _xshift == 3 || _xshift == 4 || _xshift == 5 || _xshift == 6 || _xshift == 7 || _xshift == 8))
    {
        for (int y = 47; y <= 49; y++)
        {
            for (int x = 78; x <= 89; x++)
            {
                map_array[y][x] = 0;
            }
        }
    }
    //printf("Map: first_door_check ended");
}