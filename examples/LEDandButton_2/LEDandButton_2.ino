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
bool ledState = LOW;

void setup() {
  // initialize object
  button.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // check if run() updated the debounce state
  if (button.run() == true) {
    // get debounced input state and light LED accordingly
    if (button.getDebounceState() == DEBOUNCE_PRESSED) {
      // toggle LED state
      ledState = !ledState;
  	  // write new state to LED
      digitalWrite(LED_PIN, ledState);
    }
  }
}
