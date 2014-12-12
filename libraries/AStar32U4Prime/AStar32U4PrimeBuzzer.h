// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/*! \file AStar32U4PrimeBuzzer.h */

#pragma once

#include <PololuBuzzer.h>

/*! \brief Main class for interfacing with the A-Star 32U4 Prime Buzzer.
 *
 * This class uses Timer 4 and pin 6 (PD7/OC4D) to play beeps and melodies on
 * the A-Star 32U4 Prime Buzzer.
 *
 * Note durations are timed using a timer overflow interrupt
 * (`TIMER4_OVF`), which will briefly interrupt execution of your
 * main program at the frequency of the sound being played. In most cases, the
 * interrupt-handling routine is very short (several microseconds). However,
 * when playing a sequence of notes in `PLAY_AUTOMATIC` mode (the default mode)
 * with the `play()` command, this interrupt takes much longer than normal
 * (perhaps several hundred microseconds) every time it starts a new note. It is
 * important to take this into account when writing timing-critical code.
 */
class AStar32U4PrimeBuzzer : public PololuBuzzer
{
    // This is a trivial subclass of PololuBuzzer; it exists because we wanted
    // the A-Star class names to be consistent and we didn't just use a typedef
    // to define it because that would make the Doxygen documentation harder to
    // understand.
};
