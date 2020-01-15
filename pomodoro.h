#ifndef __POMODORO_H

#define __POMODORO_H

#include "hardware.h"
#include "states.h"

#include <QuadDisplay2.h>

#define MAIN_LED_PIN 1
#define BUTTON_LED_PIN 2
#define BUTTON_PIN 3
#define DISPLAY_PIN A5

// Main class for pomodoro timer.
// Tracks current state. Provides interface for hardware (leds, button, display).
class Pomodoro {

  private:
  
    Led mainLed = Led(MAIN_LED_PIN);
    Led buttonLed = Led(BUTTON_LED_PIN);
    Button button = Button(BUTTON_PIN);
    QuadDisplay display = QuadDisplay(DISPLAY_PIN);

    PomodoroState* current;

    Initialize* initialState;
    Prepare* prepareState;
    Work* workState;
    Finished* finishedState;
    Intermission* intermissionState;

    void enter(PomodoroState* state);

  public:
    Pomodoro();
    void offButtonLed();
    void onMain();
    void offMain();
    void blinkMain();
    void show();
    void show(int minutes, int seconds);
    boolean isButtonPressed();
    // ------------------------------------------
    void initial();
    void prepare();
    void work();
    void finished();
    void intermission();
    // ------------------------------------------
    void buttonPressed();
    void time(int millis);
};

#endif
