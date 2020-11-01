/* 
 * controlLights.ino
 * 
 * uses an SNES controller to turn on and off LEDs according to the following rules:
 * 		- press and hold A and B simultaneously to turn on an LED on pin 4 (AND_PIN)
 * 		- press and hold any direction on the D-pad to turn on an LED on pin 5 (OR_PIN)
 * 
 * 
 * Author: Kyle Mitard
 * Created 28 Oct 2020
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

// controller pins
const int CLOCK = 7;
const int LATCH = 8;
const int DATA  = 9;

// LED pins
const int AND_PIN = 4;
const int OR_PIN  = 5;

// SNES controller object
SNESController snes(CLOCK, DATA, LATCH);

const long AND_BUTTONS[] = {SNES_A_BUTTON, SNES_B_BUTTON};
const long OR_BUTTONS[] = {SNES_DPAD_UP, SNES_DPAD_DOWN, SNES_DPAD_LEFT, SNES_DPAD_RIGHT};

void setup()
{
	// setup pins for LEDs
	pinMode(AND_PIN, OUTPUT);
	pinMode(OR_PIN, OUTPUT);

	// initialize SNES controller
	snes.initialize();
}

void loop()
{
	// read the controller
	snes.update();

	// check if both A and B are pressed, and update LED accordingly
	if (snes.andPressed(AND_BUTTONS))
	{
		digitalWrite(AND_PIN, HIGH);
	}
	else
	{
		digitalWrite(AND_PIN, LOW);
	}
	
	// check if any of the dpad buttons are pressed, and update LED accordingly
	if (snes.orPressed(OR_BUTTONS))
	{
		digitalWrite(OR_PIN, HIGH);
	}
	else
	{
		digitalWrite(OR_PIN, LOW);
	}
}
