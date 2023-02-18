//
// Created by lhhlu on 2/9/2023.
//

#include "Arduino.h"
#include "Button.h"

Button::Button(unsigned char p) {
    this->pin = p;
}

void Button::setup() const {
    pinMode(this->pin, INPUT);
}

void Button::setState(bool s) {
    this->state = s;
}

bool Button::getPreviousState() const {
    return this->state;
}

bool Button::readPin() const {
    return digitalRead(this->pin);
}
