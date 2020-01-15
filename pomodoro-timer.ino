#include "pomodoro.h"

#define WAIT_MILLIS 10
#define BUTTON_PRESSED_WAIT 100

// *************************************************************************

Pomodoro pomodoro;

void setup() {
}

void loop() {
  if (pomodoro.isButtonPressed()) {
    pomodoro.buttonPressed();
    delay(BUTTON_PRESSED_WAIT);
  } else {
    delay(WAIT_MILLIS);
    pomodoro.time(WAIT_MILLIS);
  }
}
