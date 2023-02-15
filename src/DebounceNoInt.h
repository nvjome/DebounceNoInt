#ifndef DebounceNoInt_h
#define DebouncNoInt_h

#include "Arduino.h"

enum debounce_state {HIGH, LOW, RISE, FALL, NOISE};

class DebounceNoInt {
    public:
        DebounceNoInt(int pin, int mode, unsigned long debounce_time_us);
        virtual ~DebounceNoInt();
        void begin();
        debounce_state update();
        debounce_state getState();
    
    private:
        int pin_;
        int mode_;
        unsigned long debounce_time_us_;
        unsigned long debounce_interval_us_ = 0;
        uint8_t history_ = 0;
        debounce_state state_ = NOISE;	// safe default state
        unsigned long last_debounce_micros_ = 0;
};

#endif
