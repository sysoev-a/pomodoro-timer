#include "hardware.h"

#include <Arduino.h>

Led::Led(int pin) {
  this->pin = pin;
  this->state = ON;
  pinMode(this->pin, OUTPUT);
}

void Led::on() {
  if (state == OFF) {
    state = ON;
    digitalWrite(pin, HIGH);      
  }
}

void Led::off() {
  if (state == ON) {
    state = OFF;
    digitalWrite(pin, LOW);
  }
}

void Led::blink() {
  if (state == OFF) {
    on();
  } else {
    off();
  }
}

// *************************************************************************

Button::Button(int pin) {
  this->pin = pin;
  pinMode(this->pin, INPUT_PULLUP);
}

bool Button::isPressed() {
  bool pressed = (LOW == digitalRead(pin));
  if (pressed) {
    // wait until button is released
    while (LOW == digitalRead(pin));
  }
  return pressed;
}
