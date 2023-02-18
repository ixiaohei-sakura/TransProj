//
// Created by lhhlu on 2/10/2023.
//

#include "Arduino.h"
#include "PowerSupply.h"

double V_RATIO = 5.00 / 1024.00;

PowerSupply::PowerSupply(unsigned char bat_5, unsigned char on_board_5, unsigned char s) {
    this->bat = bat_5;
    this->ob = on_board_5;
    this->stat = s;
}

void PowerSupply::setup() const {
    pinMode(this->bat, INPUT);
    pinMode(this->ob, INPUT);
    pinMode(this->stat, INPUT);
}

double PowerSupply::batVoltage() const {
    return analogRead(this->bat) * V_RATIO;
}

double PowerSupply::obVoltage() const {
    return analogRead(this->ob) * V_RATIO;
}

double PowerSupply::batPercentage() const {
    if (!digitalRead(this->stat)) return 100.00;
    return (this->batVoltage() / 4.20) * 100.00;
}
