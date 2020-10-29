/*
 * SNES.cpp
 * 
 * Arduino library for reading an SNES Controller
 * 
 * Author: Kyle Mitard
 * Created 26 Oct 2020
 * 
 * 
 * pinout for SNES controller is as follows:
 * 
 * ┌────────────────┬───────────\
 * │	O	 O	 O	 O │ O	 O	 O	)
 * └────────────────┴───────────/
 *		1	 2	 3	 4	 5	 6	 7
 * 
 * 1 => 5V
 * 2 => Clock
 * 3 => Latch
 * 4 => Data
 * 5 => N/C
 * 6 => N/C
 * 7 => Ground
 * 
 * 
 * The easiest way to get a good connection is to cut the cable and figure out
 * which wire goes to which pin using a multimeter. If you're like me and you
 * don't like to mutilate genuine hardware, you can find an extension cable.
 * 
 * 
 * This is just a refactoring of some code I found online, and while I am reasonably
 * confident that I know how it (and by extension the SNES controller) works, my
 * comments may be wrong. Nonetheless, the code this is originally based on can be
 * found here:
 * https://gist.github.com/zvodd/252203e9b1dbc905e721
 * 
 */


#include "SNES.h";
#include "Arduino.h";


/*
	* Instantiates a SNES controller with the given pins
	* 
	* Params:
	* clock = Arduino pin at where clock is connected (see pinout)
	* data	= Arduino pin at where data is connected (see pinout)
	* latch = Arduino pin at where latch is connected (see pinout)
	*/
SNESController::SNESController(int clockPin, int dataPin, int latchPin)
{
	// set instance variables
	_clockPin = clockPin;
	_dataPin = dataPin;
	_latchPin = latchPin;
}


/*
 * initializes the SNES controller by setting up pins
 */
void SNESController::initialize()
{
	// set pins
	pinMode(_latchPin, OUTPUT);
	pinMode(_clockPin, OUTPUT); 
	pinMode(_dataPin, INPUT);
}


/*
 * reads the controller
 */
void SNESController::update()
{
	// briefly pull latch high to signal data coming in
	digitalWrite(_latchPin, HIGH);
	delayMicroseconds(12);
	digitalWrite(_latchPin, LOW);
	

	int currentButton;

	//initialize controller data as zero ()
	_controllerData = 0;
	
	for (int i = 0; i < 12; i++)
	{
		// after falling edge of clock pulse, read data pin
		digitalWrite(_clockPin, LOW);
		delayMicroseconds(0.2);
		
		// 0 Indicates button pressed for SNES controller
		currentButton = digitalRead(_dataPin);

		// if button is pressed, update controllerData 
		if (!currentButton)
		{
			_controllerData = _controllerData | ((long)1 << i);
		}

		// rising edge of clock pulse
		digitalWrite(_clockPin, HIGH);
	}
}


/*
 * returns the data from the last time the controller was updated in the form of
 * 12 bits, where each bit represents a button.
 */ 
long SNESController::getData()
{
	return _controllerData;
}


/*
 * returns true if the given button is pressed, false otherwise
 * 
 * Params:
 * button = the button to check
 */
bool SNESController::pressed(int button)
{
	return _controllerData & button;
}


/*
 * returns true if all of the buttons in the array have been pressed
 * 
 * Params:
 * buttons = the buttons to check
 */
bool SNESController::andPressed(int buttons[])
{
	for (int b: buttons)
	{
		if (!(_controllerData & b))
		{
			return false;
		}
	}
	return true;
}


/*
 * returns true if only one of the buttons in the array have been pressed
 * 
 * Params:
 * button = the buttons to check
 */
bool SNESController::orPressed(int buttons[])
{
	for (int b: buttons)
	{
		if (_controllerData & b)
		{
			return true;
		}
	}
	return false;
}
}