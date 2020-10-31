/*
 * VVVVVV_SNES.ino
 * 
 * binds SNES controller inputs to the keyboard to play VVVVVV
 * 
 *   SNES |  Key  |   VVVVVV
 * -------+-------+-----------
 *    B   |   Z   | Action
 *    X   | Enter | Enter
 *  Start |  Esc  | Quit
 *  Left  | Left  | Move Left
 *  Right | Right | Move Right
 * 
 * Author: Kyle Mitard
 * Created 30 Oct 2020
 * 
 * pinout for SNES controller is as follows:
 * 
 * ┌────────────────┬───────────\
 * │  O   O   O   O │ O   O   O  )
 * └────────────────┴───────────/
 *    1   2   3   4   5   6   7
 * 
 * 
 *  Usage | SNES | Arduino
 * -------+------+---------
 *   5V   |  1   |   5V
 *  Clock |  2   |    7 
 *  Latch |  3   |    8
 *  Data  |  4   |    9
 * Ground |  7   |   GND
 * 
 * The easiest way to get a good connection is to cut the cable and figure out
 * which wire goes to which pin using a multimeter. If you're like me and you
 * don't like to mutilate genuine hardware, you can use an extension cable.
 * 
 */

#include "SNES.h";
#include "Keyboard.h";

// controller pins
const int CLOCK = 7;
const int LATCH = 8;
const int DATA  = 9;

// SNES controller object
SNESController snes(CLOCK, DATA, LATCH);

// kill switch for when things inevitably go wrong
const int KILL_SWITCH = 13;


void setup()
{
	snes.initialize();
	Keyboard.begin();
	pinMode(KILL_SWITCH, INPUT_PULLUP);
}

void loop() 
{
	// check for the kill switch before doing anything
	if (digitalRead(KILL_SWITCH) == LOW)
	{
		snes.update();

        
        if (snes.pressed(SNES_DPAD_LEFT))
        {
            Keyboard.press(KEY_LEFT_ARROW);
        }
        else
        {
            Keyboard.release(KEY_LEFT_ARROW);
        }

        
        if (snes.pressed(SNES_DPAD_RIGHT))
        {
            Keyboard.press(KEY_RIGHT_ARROW);
        }
        else
        {
            Keyboard.release(KEY_RIGHT_ARROW);
        }


        if (snes.pressed(SNES_START_BUTTON))
        {
            Keyboard.press(KEY_ESC);
        }
        else
        {
            Keyboard.release(KEY_ESC);
        }

        
        if (snes.pressed(SNES_B_BUTTON))
        {
            Keyboard.press('z');
        }
        else
        {
            Keyboard.release('z');
        }

        
        if (snes.pressed(SNES_X_BUTTON))
        {
            Keyboard.press(KEY_RETURN);
        }
        else
        {
            Keyboard.release(KEY_RETURN);
        }
	}
}
