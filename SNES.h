/*
 * SNES.h
 * 
 * Header file for SNES Controller library
 * 
 * Author: Kyle Mitard
 * Created 26 Oct 2020
 * 
 * 
 * pinout for SNES controller is as follows:
 * 
 * ┌────────────────┬───────────\
 * │  O   O   O   O │ O   O   O  )
 * └────────────────┴───────────/
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

#ifndef SNES_h
#define SNES_h
#endif

// hex codes for buttons
#define SNES_B_BUTTON 		0x0001
#define SNES_Y_BUTTON		0x0002
#define SNES_SELECT_BUTTON	0x0004
#define SNES_START_BUTTON	0x0008
#define SNES_DPAD_UP		0x0010
#define SNES_DPAD_DOWN		0x0020
#define SNES_DPAD_LEFT		0x0040
#define SNES_DPAD_RIGHT		0x0080
#define SNES_A_BUTTON		0x0100
#define SNES_X_BUTTON		0x0200
#define SNES_L_BUTTON		0x0400
#define SNES_R_BUTTON		0x0800


class SNESController
{
public:
	/*
	 * Instantiates a SNES controller with the given pins
	 * 
	 * Params:
	 * clock = Arduino pin at where clock is connected (see pinout)
	 * data  = Arduino pin at where data is connected (see pinout)
	 * latch = Arduino pin at where latch is connected (see pinout)
	 */
	SNESController(int clockPin, int dataPin, int latchPin);

	/*
	* initializes the SNES controller by setting up pins
	*/
	void initialize();

	/*
	 * reads the controller
	 */
	void update();

	/*
	 * returns the data from the last time the controller was updated in the form of
	 * 12 bits, where each bit represents a button.
	 */ 
	long getData();

	/*
	 * returns true if the given button is pressed, false otherwise
	 * 
	 * Params:
	 * button = the button to check
	 */
	bool pressed(int button);

	/*
	 * returns true if all of the buttons in the array have been pressed
	 * 
	 * Params:
	 * buttons = the buttons to check
	 */
	bool andPressed(int buttons[]);

	/*
	 * returns true if only one of the buttons in the array have been pressed
	 * 
	 * Params:
	 * button = the buttons to check
	 */
	bool orPressed(int buttons[]);

private:
	
	// serial clock for controller
	int _clockPin;

	// controller serial data output
	int _dataPin;

	// latch pin pulled high to signify when new data is coming in
	int _latchPin;

	// the data from the last time the controller was read
	long _controllerData;
};