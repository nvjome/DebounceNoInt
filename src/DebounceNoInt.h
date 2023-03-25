#ifndef DebounceNoInt_h
#define DebouncNoInt_h

#include "Arduino.h"

enum State {DB_HIGH, DB_LOW, DB_RISE, DB_FALL, DB_NOISE};

class DebounceNoInt {
    public:
        DebounceNoInt(int pin, int mode, unsigned long debounce_time_us);
        virtual ~DebounceNoInt();
        void begin();
        State update();
        State getState();
        bool isRisen();
        bool isFallen();
        bool isHigh();
        bool isLow();
    
    private:
        int pin_;
        int mode_;
        unsigned long debounce_time_us_;
        unsigned long debounce_interval_us_ = 0;
        uint8_t history_ = 0;
        State state_ = DB_NOISE;	// safe default state
        unsigned long last_debounce_micros_ = 0;
};

#endif
