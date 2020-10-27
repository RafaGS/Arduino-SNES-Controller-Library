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

