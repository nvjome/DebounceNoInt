#include "DebounceNoInt.h"
#include "Arduino.h"

/*
    DebounceNoInt
    
    Constructor for debounce object.
*/
DebounceNoInt::DebounceNoInt(int pin, int mode, unsigned long debounce_time_us) {
    pin_ = pin;
    mode_ = mode;
    debounce_time_us_ = debounce_time_us;
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
	pinMode(pin_, mode_);

	// Time between pin reads is total debounce time divided by length of history,
	// hardcoded here as 8. This could be changed, but 8 seems to be long enough,
	// and fits in one uint_8 variable.
	debounce_interval_us = debounce_time_us_ / 8;
}

/*
	update

	Performs the debounce algorithm. Must be called periodically and as often as
	possible for best debouncing results. Returns true if the algorithm was run.
	Return false if the debounce interval time was not met and the debounce state
	was not updated.
*/
bool DebounceNoInt::update() {
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
				_state = FALL;
			} else {
				_state = RISE;
			}
			break;
		case 0b01111111:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				_state = RISE;
			} else {
				_state = FALL;
			}
			break;
		case 0b00000000:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				_state = HIGH;
			} else {
				_state = LOW;
			}
			break;
		case 0b11111111:
			if (_active_high_low == DEBOUNCE_ACTIVE_LOW) {
				_state = LOW;
			} else {
				_state = HIGH;
			}
			break;
		default:
			_state = DEBOUNCE_NOISE;
		}

		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}

/*
	getState

	Returns the current debounced input state. Includes a noise state for when the
	input is detected as bouncing. This DOES NOT run the debouncing algorithm, run() MUST
	be called to update the input state!
*/
debounce_state DebounceNoInt::getState() {
	return _state;
}
