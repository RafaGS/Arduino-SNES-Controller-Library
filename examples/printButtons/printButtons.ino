/* 
 *  printButtons.ino
 * 
 * prints all of the buttons that are pressed into the serial monitor.
 * 
 * Author: Kyle Mitard
 * Created 26 Oct 2020
 * 
 * 
 * pinout for SNES controller is as follows:
 * 
 * -----------------------------\
 * |  O   O   O   O | O   O   O  )
 * -----------------------------/
 *    1   2   3   4   5   6   7
 * 
 * 1 => 5V
 * 2 => Clock
 * 3 => Latch
 * 4 => Data
 * 5 => N/C
 * 6 => N/C
 * 7 => Ground
 * 
 * The easiest way to get a good connection is to cut the cable and figure out
 * which wire goes to which pin using a multimeter. If you're like me and you
 * don't like to mutilate genuine hardware, you can use an extension cable.
 * 
 */


#include "SNES.h";

// pins
const int CLOCK = 7;
const int LATCH = 8;
const int DATA  = 9;

// SNES controller object
SNESController snes(CLOCK, DATA, LATCH);

// the input from the controller
long input;

// all of the buttons
const long BUTTONS[] = { SNES_A_BUTTON,	SNES_B_BUTTON,   SNES_X_BUTTON,		SNES_Y_BUTTON,
						SNES_L_BUTTON,	SNES_R_BUTTON,   SNES_DPAD_UP,		SNES_DPAD_DOWN,
						SNES_DPAD_LEFT, SNES_DPAD_RIGHT, SNES_START_BUTTON, SNES_SELECT_BUTTON };

// the corresponding names of the buttons
const char* NAMES[] = { "A", "B", "X", "Y", 
						"L", "R", "up", "down",
						"left", "right", "start", "select" };

void setup()
{
	Serial.begin(9600);

	snes.initialize();
}

void loop()
{
	snes.update();
	for (int i = 0; i < 12; i++)
	{
		if (snes.pressed(BUTTONS[i]))
		{
			Serial.print(NAMES[i]);
      Serial.print(", ");
		}
	}
	Serial.print("\n");
}
