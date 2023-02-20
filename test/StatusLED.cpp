//
// Created by lhhlu on 2022/12/3.
//

#include "Arduino.h"
#include "StatusLED.h"

StatusLED::StatusLED(unsigned int LEDPin) {
    this->pin = LEDPin;
}

void StatusLED::setup() const {
    pinMode(this->pin, OUTPUT);
}

void StatusLED::turnOn() {
    digitalWrite(this->pin, HIGH);
    this->status = true;
}

void StatusLED::turnOff() {
    digitalWrite(this->pin, LOW);
    this->status = false;
}

void StatusLED::toggle() {
    if (this->status) {
        this->turnOff();
    } else {
        this->turnOn();
    }
}

void StatusLED::adjBrightness(int bri) {
    analogWrite(this->pin, bri);
    this->status = false;
}

void StatusLED::blink(int times, int interval) {
    for (int i = 0; i < times; i++){
        this->turnOn();
        delay(interval);
        this->turnOff();
        delay(interval);
    }
}
