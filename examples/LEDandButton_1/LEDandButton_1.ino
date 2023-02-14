/*
 * Example sketch of using the DebounceNoInt library.
 * https://github.com/nvjome/DebounceNoInt
 * 
 * Turns on LED when a button is pressed, turns off when released.
 * Uses DEBOUNCE_RISE and DEBOUNCE_FALL states to detect button and control LED.
 * 
 * Written by nvjome.
 */

#include <DebounceNoInt.h>

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN 4

// create debounce object
// attach to button pin, buton active low, 5ms debounce time, internal pullup active (true)
DebounceNoInt button(BUTTON_PIN, DEBOUNCE_ACTIVE_LOW, 5000, true);

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
  if (updateB ==  true) {
    // get debounced input state and light LED accordingly
    if (button.getDebounceState() == DEBOUNCE_ON) {
      // button pressed
      digitalWrite(LED_PIN, HIGH);
    }
    if (button.getDebounceState() == DEBOUNCE_OFF) {
      // button released
      digitalWrite(LED_PIN, LOW);
    }
  }
}
