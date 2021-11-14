#ifndef DebounceNoInt_h
#define DebouncNoInt_h

class DebounceNoInt {
	public:
		debounceNoInt(int pin, uint8_t activeHL, unsigned long interval);
		virtual ~DebounceNoInt();
	
	
	private:
		int _pin;
		uint8_t _activeHL;
		unsigned lon _interval;
	
};

#endif