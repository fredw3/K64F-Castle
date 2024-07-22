#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init(N5110 &lcd, Bitmap &bitmap)
{
    //printf("Engine initialisation called");
    
    _map.init(lcd);
    _player.init(lcd, bitmap);
    
    //_sprite.init();
    
    //printf("Engine initialisation ended");
    
}

void Engine::read(N5110 &lcd, Gamepad &pad)
{
    //printf("Engine read called");
    
    _player.read(pad);
    _map.read(lcd, pad);
    
    //printf("Engine read ended");
}

void Engine::update(Gamepad &pad, N5110 &lcd, Bitmap &bitmap)
{
    //printf("Engine: update called");
    
    // Check if user is pressing A and if they either have the key or are opening the door
    if (pad.check_event(Gamepad::A_PRESSED) == true)
            {
                _map.first_key_check(lcd);
                _map.first_door_check();
            }
    _map.update(lcd);
    _player.update(lcd, bitmap, _map);
    
    // Perform checks on whether the player is adjacent to the sprite
    //check_damages();
    
    //printf("Engine: update ended");
}


void Engine::check_damages()
{
    //printf("Engine: check_damages called");
    
    int dmg_collision = 0;
    
    //printf("dmg_collision = %d", dmg_collision);
    
    // Compare all x coordinates on Player and Sprite objects
    for (int a = 0; a <= 21; a++)
    {
        for (int b = 0; b <= 21; b++)
        {
            // If any coordinates on one are adjacent to any on the other
            if (abs(_player.x_coord[a] - _sprite.x_coord[b]) == 1)
            {
                dmg_collision += 1;
                
                //printf("dmg_collision = %d", dmg_collision);
            }
        }
    }
    // Compare all y coordinates
    for (int a = 0; a <= 21; a++)
    {
        for (int b = 0; b <= 21; b++)
        {
            if (abs(_player.y_coord[a] - _sprite.y_coord[b]) == 1)
            {
                dmg_collision += 1;
                
                //printf("dmg_collision = %d", dmg_collision);
            }
        }
    }
    _player.set_dmg_collision(dmg_collision);
    
    //printf("Engine: check_damages ended");
}

bool Engine::damage_occur()
{
    //printf("Engine: damage_occur called");
    
    if (_player.get_dmg_collision() != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    //printf("Engine: damage_occur ended");
}

void Engine::update_health(int func)
{
    //printf("Engine: update_health called");
    
    _player.update_health(func);
    
    //printf("Engine: update_health ended");
}

int Engine::get_health()
{
    //printf("Engine: get_health called");
    
    int health = _player.get_health();
    
    //printf("health = %d", health);
    
    return health;
    
    //printf("Engine: get_health ended");
}

void Engine::render_health(N5110 &lcd)
{
    //printf("Engine: render_health called");
    
    _player.render_health(lcd);
    
    //printf("Engine: render_health ended");
}
