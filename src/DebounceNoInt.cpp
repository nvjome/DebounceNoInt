#include "Arduino.h"
#include "DebounceNoInt.h"

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
    debounce_interval_us_ = debounce_time_us_ / 8;
}

/*
    update

    Performs the debounce algorithm. Must be called periodically and as often as
    possible for best debouncing results. Returns true if the algorithm was run.
    Return false if the debounce interval time was not met and the debounce state
    was not updated.
*/
State DebounceNoInt::update() {
    State nstate = state_;

    // if state was changed to an edge last update(), change to corresponding next state
    if (state_ == RISE) {
        nstate = HIGH;
    }
    if (state_ == FALL) {
        nstate = LOW;
    }
    
    unsigned long curr_debounce_micros = micros();

    // check micros time to take new input reading
    if ((curr_debounce_micros - last_debounce_micros_) >= debounce_interval_us_) {
        // reset previous micros time reading
        last_debounce_micros_ = curr_debounce_micros;
        // prepare history for new input reading
        history_ <<= 1;
        
        // if input is high, set LSB to 1
        // if input is low, set LSB to 0
        if (digitalRead(pin_)) {
            history_ |= 0x01;
        } else {
            history_ &= ~0x01;
        }

        switch (state_) {
            case HIGH:
                // only check for FALL in HIGH state
                if (history_ == 0b10000000) {
                    nstate = FALL;
                }
                break;
            case LOW:
                // only check for RISE in LOW state
                if (history_ == 0b01111111) {
                    nstate = RISE;
                }
                break;
            default:
                ; // must bounce or noise, do nothing
        }

        // update debounce state based on input history
        /*switch (history_) {
            case 0b10000000:
                state_ = FALL;
                break;
            case 0b01111111:
                state_ = RISE;
                break;
            default:
                ; // must be bounce, don't change state
        }*/
    }

    state_ = nstate;
    return state_;
}

/*
    getState

    Returns the current debounced input state. Includes a noise state for when the
    input is detected as bouncing. This DOES NOT run the debouncing algorithm, run() MUST
    be called to update the input state!
*/
State DebounceNoInt::getState() {
    return state_;
}
