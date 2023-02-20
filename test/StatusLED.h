//
// Created by lhhlu on 2022/12/3.
//

#ifndef TRANSSIDELOGIC_STATUSLED_H
#define TRANSSIDELOGIC_STATUSLED_H


class StatusLED {
public:
    explicit StatusLED(unsigned int pin = 13);
    void setup() const;
    void turnOn();
    void turnOff();
    void toggle();
    void adjBrightness(int bri);
    void blink(int times, int interval);
    unsigned int pin;
private:
    bool status = false;
};


#endif //TRANSSIDELOGIC_STATUSLED_H
