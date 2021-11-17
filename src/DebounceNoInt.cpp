#include "DebounceNoInt.h"
#include "Arduino.h"

/*
    DebounceNoInt
    
    Constructor for debounce object.
*/
DebounceNoInt::DebounceNoInt(int pin, uint8_t active_high_low, unsigned long debounce_time_us, bool pullup) {
    _pin = pin;
    _active_high_low = active_high_low;
    _debounce_time_us = debounce_time_us;
    _pullup = pullup;
}

/*
    ~DebounceNoInt

    Default deconstructor.
*/
DebounceNoInt::~DebounceNoInt() {
    ;
}

/*
	begin

	Initializes hardware related to object, along with some private attributes.
    Does no checking to determine if the desired pin is valid.
*/
void DebounceNoInt::begin() {
	if (_pullup == true) {
		pinMode(_pin, INPUT_PULLUP);
	} else {
		pinMode(_pin, INPUT);
	}

	// Time between pin reads is total debounce time divided by length of history,
	// hardcoded here as 8. This could be changed, but 8 seems to be long enough,
	// and fits in one uint_8 variable.
	debounce_interval_us = _debounce_time_us / 8;
}

/*
	run

	Performs the debounce algorithm. Must be called periodically and as often as
	possible for best debouncing results. Returns true if the algorithm was run.
	Return false if the debounce interval time was not met and the debounce state
	was not updated.
*/
bool DebounceNoInt::run() {
	bool ret;
	// get current micros time
	curr_debounce_micros = micros();

	// check micros time to take new input reading
	if ((curr_debounce_micros - last_debounce_micros) >= debounce_interval_us) {
		// reset previous micros time reading
		last_debounce_micros = curr_debounce_micros;
		// prepare history for new input reading
		history <<= 1;
		
		// if input is high, set LSB to 1
		// if input is low, set LSB to 0
		if (digitalRead(_pin) == true) {
			history |= 0x01;
		} else {
			history &= ~0x01;
		}

		// update debounce state based on input history
		switch (history) {
		case 0b10000000:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				debounce_state = DEBOUNCE_PRESSED;
			} else {
				debounce_state = DEBOUNCE_RELEASED;
			}
			break;
		case 0b01111111:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				debounce_state = DEBOUNCE_RELEASED;
			} else {
				debounce_state = DEBOUNCE_PRESSED;
			}
			break;
		case 0b00000000:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				debounce_state = DEBOUNCE_ON;
			} else {
				debounce_state = DEBOUNCE_OFF;
			}
			break;
		case 0b11111111:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				debounce_state = DEBOUNCE_OFF;
			} else {
				debounce_state = DEBOUNCE_ON;
			}
			break;
		default:
			debounce_state = DEBOUNCE_NOISE;
		}

		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}

/*
	getDebounceState

	Returns the current debounced input state. Includes a noise state for when the
	input is detected as bouncing. This DOES NOT run the debouncing algorithm, run() MUST
	be called to update the input state!
*/
uint8_t DebounceNoInt::getDebounceState() {
	return debounce_state;
}

/*
	runAndGetDebounceState

	Equivalent to calling run the immediately calling getDebounceState. Returns the current debounced input state,
	or the previous state if the state was not updated by run.
*/
uint8_t DebounceNoInt::runAndGetDebounceState() {
	run();
	uint8_t state = getDebounceState();

	return state;
}