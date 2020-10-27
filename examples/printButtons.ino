/*
 * printButtons.ino
 * 
 * prints all of the buttons that are pressed into the serial monitor.
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
 * The easiest way to get a good connection is to cut the cable and figure out
 * which wire goes to which pin using a multimeter. If you're like me and you
 * don't like to mutilate genuine hardware, you can use an extension cable.
 * 
 */


#include "SNES.h";

void setup()
{
	Serial.begin(9600);

}

void loop()
{

}