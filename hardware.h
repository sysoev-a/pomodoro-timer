#ifndef __HARDWARE_H

#define __HARDWARE_H

#define ON 1
#define OFF 0

// class to switch led on/off
class Led {
  
  private:
  
    int pin;
    int state;

  public:

    Led(int pin);
    void on();
    void off();
    void blink();
};

// class to check button state
class Button {
  
  private:
  
    int pin;

  public:
  
    Button(int pin);
    bool isPressed();
};

#endif
