#include "pomodoro.h"

#include <QuadDisplay2.h>

void Pomodoro::enter(PomodoroState* state) {
  current = state;
  current->enter();
}

// ------------------------------------------

Pomodoro::Pomodoro() {
  display.begin();
  
  initialState = new Initialize(this);
  prepareState = new Prepare(this);
  workState = new Work(this);
  finishedState = new Finished(this);
  intermissionState = new Intermission(this);

  initial();
}

void Pomodoro::offButtonLed() {
  buttonLed.off();
}

void Pomodoro::onMain() {
  mainLed.on();
}

void Pomodoro::offMain() {
  mainLed.off();    
}

void Pomodoro::blinkMain() {
  mainLed.blink();
}

void Pomodoro::show() {
  display.displayClear();
}

void Pomodoro::show(int minutes, int seconds) {
  display.displayScore(minutes, seconds);
}

boolean Pomodoro::isButtonPressed() {
  return button.isPressed();
}

// ------------------------------------------

void Pomodoro::initial() {
  enter(initialState);
}

void Pomodoro::prepare() {
  enter(prepareState);
}

void Pomodoro::work() {
  enter(workState);
}

void Pomodoro::finished() {
  enter(finishedState);
}

void Pomodoro::intermission() {
  enter(intermissionState);
}

// ------------------------------------------

void Pomodoro::buttonPressed() {
  current->buttonPressed();
}

void Pomodoro::time(int millis) {
  current->time(millis);
}
