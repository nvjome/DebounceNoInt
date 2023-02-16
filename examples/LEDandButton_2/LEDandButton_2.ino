/*
 * Example sketch of using the DebounceNoInt library.
 * https://github.com/nvjome/DebounceNoInt
 * 
 * Toggles on LED when a button is pressed, toggles off when pressed again.
 * Uses FALL state to detect button and control LED.
 */

#include <DebounceNoInt.h>

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN 4

// create debounce object
// attach to button pin, input pullup mode, 5ms debounce time
DebounceNoInt button(BUTTON_PIN, INPUT_PULLUP, 5000);

// LED state variable
bool ledState = LOW;

void setup() {
  // initialize object
  button.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  button.update();

  // get debounced input state and light LED accordingly
  if (button.isFallen() == true) {
    // toggle LED state
    ledState = !ledState;
    // write new state to LED
    digitalWrite(LED_PIN, ledState);
  }
}