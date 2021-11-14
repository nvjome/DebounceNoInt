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

    Default doceonstructor.
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
	getDebounceState

	Returns the current debounced input state. Includes a noise state for when the
	input is detected as bouncing. This DOES NOT run the debouncing algorithm, run() MUST
	be called to update the input state! This was done to make this function as fast as possible,
	and allow flexability in choosing where in the application the input state gets updated.
*/
uint8_t DebounceNoInt::getDebounceState() {
	return debounce_state;
}

/*
	run

	Performs the debounce algorithm. Must be called periodically and as often as
	possible for best debouncing results. Returns true if the algorithm was run.
	Return false if the debounce interval time was not met and the debounce state
	was not updated.
*/
bool DebounceNoInt::run() {
	curr_debounce_micros = micros();
	bool ret;

	// check if time to take new input reading
	if ((curr_debounce_micros - last_debounce_micros) >= debounce_interval_us) {
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
			debounce_state = DEBOUNCE_FALL;
			break;
		case 0b00000001:
			debounce_state = DEBOUNCE_RISE;
			break;
		case 0b00000000:
			debounce_state = DEBOUNCE_LOW;
			break;
		case 0b11111111:
			debounce_state = DEBOUNCE_HIGH;
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