#ifndef DebounceNoInt_h
#define DebouncNoInt_h

#include "Arduino.h"

#define DEBOUNCE_OFF 0x00
#define DEBOUNCE_ON 0x01
#define DEBOUNCE_PRESSED 0x02
#define DEBOUNCE_RELEASED 0x03
#define DEBOUNCE_NOISE 0x04
#define DEBOUNCE_INVALID 0x05

#define DEBOUNCE_ACTIVE_LOW 0x00
#define DEBOUNCE_ACTIVE_HIGH 0x01

class DebounceNoInt {
	public:
		DebounceNoInt(int pin, uint8_t active_high_low, unsigned long debounce_time_us, bool pullup);
		virtual ~DebounceNoInt();
		void begin();
		bool run();
		uint8_t getDebounceState();
		uint8_t runAndGetDebounceState();
	
	private:
		int _pin;
		uint8_t _active_high_low;
		unsigned long _debounce_time_us;
		unsigned long debounce_interval_us = 0;
		bool _pullup;
		uint8_t history = 0;
		uint8_t debounce_state = DEBOUNCE_NOISE;	// safe default state
		unsigned long last_debounce_micros = 0;
		unsigned long curr_debounce_micros = 0;
};

#endif