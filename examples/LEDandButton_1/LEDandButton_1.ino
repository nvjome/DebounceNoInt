/*
 * Example sketch of using the DebounceNoInt library.
 * https://github.com/nvjome/DebounceNoInt
 * 
 * Turns on LED when a button is pressed, turns off when released.
 * Uses RISE and FALL states to detect button and control LED.
 */

#include <DebounceNoInt.h>

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN 4

// create debounce object
// attach to button pin, input pullup mode, 5ms debounce time
DebounceNoInt button(BUTTON_PIN, INPUT_PULLUP, 5000);

void setup() {
  // initialize object
  button.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // update debounce state
  button.update();

  // get debounced input state and light LED accordingly
  if (button.getState() == LOW) {
    // button pressed
    digitalWrite(LED_PIN, HIGH);
  }
  if (button.getState() == HIGH) {
    // button released
    digitalWrite(LED_PIN, LOW);
  }
}
