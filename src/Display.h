//
// Created by lhhlu on 2/10/2023.
//

#ifndef UNTITLED_DISPLAY_H
#define UNTITLED_DISPLAY_H

//#include "U8g2lib.h"
#include "../lib/U8g2/src/U8g2lib.h"
#include "RemoteData.h"
#include "PowerSupply.h"
#include "Button.h"


class Display {
public:
    Display(unsigned char CLK, unsigned char MO_SI, unsigned char CS, unsigned char R);
    void setup() const;
    void showStartUpInformation(const String& str) const;
    void drawMainPage(RemoteData &data, PowerSupply powerSupply, Button *buttons[]) const;
    U8G2_ST7920_128X64_F_SW_SPI *disInstance;
private:
    void printData(double data, int accuracy = 2, char previous_zeros = 0) const;
    void btnStatus(bool state) const;
};


#endif //UNTITLED_DISPLAY_H
