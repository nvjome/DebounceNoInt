#ifndef DebounceNoInt_h
#define DebouncNoInt_h

#include "Arduino.h"

enum debounce_state {HIGH, LOW, RISE, FALL, NOISE};

#define DEBOUNCE_ACTIVE_LOW 0x00
#define DEBOUNCE_ACTIVE_HIGH 0x01

class DebounceNoInt {
	public:
		DebounceNoInt(int pin, uint8_t active_high_low, unsigned long debounce_time_us, bool pullup);
		virtual ~DebounceNoInt();
		void begin();
		bool update();
		debounce_state getState();
	
	private:
		int _pin;
		uint8_t _active_high_low;
		unsigned long _debounce_time_us;
		unsigned long debounce_interval_us = 0;
		bool _pullup;
		uint8_t history = 0;
		debounce_state _state = NOISE;	// safe default state
		unsigned long last_debounce_micros = 0;
		unsigned long curr_debounce_micros = 0;
};

#endif
