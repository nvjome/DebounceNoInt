/*
 * Example sketch of using the DebounceNoInt library.
 * https://github.com/nvjome/DebounceNoInt
 * 
 * Toggles on LED when a button is pressed, toggles off when pressed again.
 * Uses DEBOUNCE_FALL state to detect button and control LED.
 * 
 * Written by nvjome.
 */

#include <DebounceNoInt.h>

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN 4

// create debounce object
// attach to button pin, buton active low, 5ms debounce time, internal pullup active (true)
DebounceNoInt button(BUTTON_PIN, DEBOUNCE_ACTIVE_LOW, 5000, true);

// LED state variable
uint8_t ledState = LOW;

void setup() {
  // initialize object
  button.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // update debounce state
  int updateB = button.run();

  // check if run() updated the debounce state
  if (updateB == true) {
    // get debounced input state and light LED accordingly
    if (button.getDebounceState() == DEBOUNCE_PRESSED) {
      // button pressed
  
  	// toggle LED state
  	if (ledState == LOW) {
  		ledState = HIGH;
  	} else {
  		ledState = LOW;
  	}
  
  	// write new state to LED
      digitalWrite(LED_PIN, ledState);
    }
  }
}
