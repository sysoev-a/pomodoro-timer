#ifndef __STATES_H

#define __STATES_H

class Pomodoro;

// Base class for all states.
// Provides default implementations for state methods.
class PomodoroState {

  protected:
  
    Pomodoro* pomodoro;
  
  public:

    PomodoroState(Pomodoro* pomodoro);
    virtual void enter();
    virtual void buttonPressed();
    virtual void time(int millis);
};

// -------------------------------------------------------------------------

// Initial state: all leds and display are off.
// On button transits to Prepare.
class Initialize : public PomodoroState {

  public:

    Initialize(Pomodoro* pomodoro);

    void enter();
    void buttonPressed(); 
};

// -------------------------------------------------------------------------

// Prepare state: waiting to start the pomodoro. Display shows pomodoro duration.
// On button transits to Work.
class Prepare : public PomodoroState {

  public:

    Prepare(Pomodoro* pomodoro);

    void enter();
    void buttonPressed();
};

// -------------------------------------------------------------------------

// Base class for states, based on timer.
class AbstractTimedPomodoroState : public PomodoroState {
  
  private:
  
    int millisCounter;    

  protected:

    int minutes;
    int seconds;
  
    void init(int minutes, int seconds);
    bool elapsed(int millis);

  public:
    AbstractTimedPomodoroState(Pomodoro* pomodoro);
};

// -------------------------------------------------------------------------

// Work state: pomodoro is going on. Main led on. Display shows remained time.
// On button transit to Initialize.
// On time:
//          if time elapsed transit to Finished
//          else remain in current state.
class Work : public AbstractTimedPomodoroState {

  public:

    Work(Pomodoro* pomodoro);

    void enter();
    void buttonPressed();
    void time(int millis);
};

// -------------------------------------------------------------------------

// Finished state: pomodoro has finished, need to make a break. Main led blinking. Display shows intermission duration.
// On button transit to Intermission.
// On time blink main led and remain in current state.
class Finished : public PomodoroState {
  
  private:
  
    int millisCounter;
  
  public:

    Finished(Pomodoro* pomodoro);

    void enter();
    void buttonPressed();
    void time(int millis);
};

// -------------------------------------------------------------------------

// Intermission state: break is going on. Main led off. Display shows remained time.
// On button transit to Initialize.
// On time:
//          if time elapsed transit to Initialize
//          else remain in current state.
class Intermission : public AbstractTimedPomodoroState {
  
  public:

    Intermission(Pomodoro* pomodoro);

    void enter();
    void buttonPressed();
    void time(int millis);
};

#endif
