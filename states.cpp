#include "states.h"

#include "pomodoro.h"

#define WORK_MINUTES 25
#define WORK_SECONDS 0
#define BREAK_MINUTES 5
#define BREAK_SECONDS 0

#define MILLIS_IN_SECOND 1000
#define MILLIS_TO_BLINK 1000

// -------------------------------------------------------------------------

PomodoroState::PomodoroState(Pomodoro* pomodoro) {
  this->pomodoro = pomodoro;
}

void PomodoroState::buttonPressed() {
}

void PomodoroState::time(int millis) {
}

void PomodoroState::enter() {
}

// -------------------------------------------------------------------------

Initialize::Initialize(Pomodoro* pomodoro) : PomodoroState(pomodoro) {
}

void Initialize::enter() {
  pomodoro->offMain();
  pomodoro->offButtonLed();
  pomodoro->show();
}

void Initialize::buttonPressed() {
  pomodoro->prepare();
}

// -------------------------------------------------------------------------

Prepare::Prepare(Pomodoro* pomodoro) : PomodoroState(pomodoro) {
}

void Prepare::enter() {
  pomodoro->show(WORK_MINUTES, WORK_SECONDS);
}

void Prepare::buttonPressed() {
  pomodoro->work();
}

// -------------------------------------------------------------------------

void AbstractTimedPomodoroState::init(int minutes, int seconds) {
  this->millisCounter = 0;
  this->minutes = minutes;
  this->seconds = seconds;
}

bool AbstractTimedPomodoroState::elapsed(int millis) {
  millisCounter += millis;
  if (millisCounter >= MILLIS_IN_SECOND) {
    millisCounter = 0;
    seconds--;
    if (seconds < 0) {
      seconds = 59;
      minutes--;
    }
  }
  return minutes < 0;
}

AbstractTimedPomodoroState::AbstractTimedPomodoroState(Pomodoro* pomodoro) : PomodoroState(pomodoro) {
}

// -------------------------------------------------------------------------

Work::Work(Pomodoro* pomodoro) : AbstractTimedPomodoroState(pomodoro) {
}

void Work::enter() {
  init(WORK_MINUTES, WORK_SECONDS);
  pomodoro->onMain();
}

void Work::buttonPressed() {
  pomodoro->initial();
}

void Work::time(int millis) {
  if (elapsed(millis)) {
    pomodoro->finished();
  } else {
    pomodoro->show(minutes, seconds);
  }
}

// -------------------------------------------------------------------------

Finished::Finished(Pomodoro* pomodoro) : PomodoroState(pomodoro) {
}

void Finished::enter() {
  millisCounter = 0;
  pomodoro->show(BREAK_MINUTES, BREAK_SECONDS);
  pomodoro->blinkMain();
}

void Finished::buttonPressed() {
  pomodoro->intermission();
}

void Finished::time(int millis) {
  millisCounter += millis;
  if (millisCounter >= MILLIS_TO_BLINK) {
    millisCounter = 0;
    pomodoro->blinkMain();
  }
}

// -------------------------------------------------------------------------

Intermission::Intermission(Pomodoro* pomodoro) : AbstractTimedPomodoroState(pomodoro) {
}

void Intermission::enter() {
  init(BREAK_MINUTES, BREAK_SECONDS);
  pomodoro->offMain();
}

void Intermission::buttonPressed() {
  pomodoro->initial();
}

void Intermission::time(int millis) {
  if (elapsed(millis)) {
    pomodoro->initial();
  } else {
    pomodoro->show(minutes, seconds);
  }
}
