////////////////////////////NOTE//////////////////////////////////////////

// All code commented out (except printf() statements) is code that I could
// not get to work in time for the deadline. Its function was meant to be 
// changing the amount of hearts at the top left of the screen depending
// on whether the player is in contact with the 8x8 block in the 2nd room,
// which would eventually resemble a sprite.

///////// pre-processor directives ////////

#include "mbed.h"
#include "Engine.h"
#include "Gamepad.h"
#include "N5110.h"
#include "Bitmap.h"
#include "Player.h"
#include "Map.h"
#include "Sprite.h"

/////////////// objects ///////////////
N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad pad;
Engine castle;
Player player;

Ticker game_ticker;
//Ticker health_tkr;

volatile int g_game_ticker_flag = 0;
//volatile int g_health_tkr_flag = 0;
//volatile int contact_flag = 0;

//bool health_ticker_active;

///////////// prototypes ///////////////
void init(N5110 &lcd, Bitmap &bitmap);
void read(N5110 &lcd, Gamepad &pad);
void update(Gamepad &pad, N5110 &lcd, Bitmap &bitmap);
void game_ticker_isr();
//void health_tkr_isr();
void welcome_screen();

///////////// functions ////////////////
int main()
{

    int fps = 8;  // frames per second

    lcd.init();
    pad.init();
    
    welcome_screen();

    game_ticker.attach(&game_ticker_isr, 1.0f/fps);
    //health_tkr.attach(&health_tkr_isr, 0.5);

    Bitmap player_array(south_array, 8, 8);

    init(lcd, player_array);
    lcd.refresh();
    
    wait(1.0f/fps);

    while (1) {

        // Main game loop
        if (g_game_ticker_flag) {
            g_game_ticker_flag = 0;
            
            read(lcd, pad);
            update(pad, lcd, player_array);

            castle.render_health(lcd);
            lcd.refresh();
        }
        /*
        if (g_health_tkr_flag)
        {
            g_health_tkr_flag = 0;
            
            if (castle.damage_occur() == true && castle.get_health() > 0)
            {
                castle.update_health(-1);
            }
            else if (castle.damage_occur() == false && castle.get_health() < 6)
            {
                castle.update_health(1);
                //contact_flag = 0;
            }
        }*/
    }
}

void init(N5110 &lcd, Bitmap &bitmap)
{
    // Game initialisations
    castle.init(lcd, bitmap);
    castle.render_health(lcd);
}

void read(N5110 &lcd, Gamepad &pad)
{
    castle.read(lcd, pad);
}

void update(Gamepad &pad, N5110 &lcd, Bitmap &bitmap)
{
    castle.update(pad, lcd, bitmap);
    
    /*
    if (castle.damage_occur() == true && contact_flag == 0)
    {
        contact_flag = 1;
        castle.update_health(-1);
        
        health_tkr.attach(&health_tkr_isr, 0.5);
        health_ticker_active = true;
    }
    
    else if (castle.damage_occur() == false && contact_flag == 0)
    {
        contact_flag = 0;
    }
    
    if (castle.get_health() == 6 && castle.damage_occur() == false && health_ticker_active == true)
    {
        health_tkr.detach();
        
        health_ticker_active = false;
    }*/
}

void game_ticker_isr()
{
    g_game_ticker_flag = 1;
}
/*
void health_tkr_isr()
{
    g_health_tkr_flag = 1;
}
*/
void welcome_screen() {
    
    lcd.printString("    CASTLE    ",0,1);  
    lcd.printString("  PRESS START   ",0,4);
    lcd.refresh();
     
    // welcome screen with text and LEDs flashing until user presses start 
    while ( pad.check_event(Gamepad::START_PRESSED) == false) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);
    }
 
}