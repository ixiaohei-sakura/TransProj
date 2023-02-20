//
// Created by lhhlu on 2/10/2023.
//

#include "Display.h"

#define DISPLAY_TICKS_LEFT_DEC 10
#define DISPLAY_TICKS_RIGHT_DEC 2

long long cd1 = 0, cd2 = 0, cda = 0;

Display::Display(unsigned char CLK, unsigned char MO_SI, unsigned char CS, unsigned char RST) {
    this->disInstance = new U8G2_ST7920_128X64_F_SW_SPI(U8G2_R0, CLK, MO_SI, CS, RST);
}

void Display::setup() const {
    this->disInstance->begin();
    this->disInstance->clear();
}

void Display::showStartUpInformation(const String& str) const {
    this->disInstance->clearBuffer();
    this->disInstance->drawFrame(0, 0, 128, 64);
    this->disInstance->setFont(u8g2_font_t0_12b_mr);
    this->disInstance->drawStr(2, 11, "Initializing...");
    this->disInstance->drawLine(0, 14, 93, 14);
    this->disInstance->drawLine(93, 14, 113, 0);
    this->disInstance->setFont(u8g2_font_squeezed_b7_tr);
    this->disInstance->drawStr(3, 48, "Status:");
    this->disInstance->setFont(u8g2_font_squeezed_b7_tr);
    this->disInstance->drawStr(3, 60, str.c_str());
    this->disInstance->sendBuffer();
}

void Display::printData(double data, int accuracy, char pz) const {
    for (char i = pz; i > 0; --i) {
        if (data < pow(10, i)) this->disInstance->print('0');
        else break;
    }
    this->disInstance->setFont(u8g2_font_t0_12b_mr);
    this->disInstance->print(data, accuracy);
}

void Display::btnStatus(bool state) const {
    this->disInstance->setFont(u8g2_font_t0_12b_mr);
    this->disInstance->print(":");
    this->disInstance->setFont(u8g2_font_t0_12b_mr);
    if (state) {
        this->disInstance->print("On");
    } else {
        this->disInstance->print("Off");
    }
}

void Display::drawMainPage(RemoteData &data, PowerSupply powerSupply, Button *buttons[]) const {
    cda++;
    if (cda < 100) return;
    cda = 0;
    
    this->disInstance->clearBuffer();
    
    this->disInstance->drawFrame(0, 0, 128, 64);
    this->disInstance->drawLine(70, 0, 70, 64);
    
    cd1++;
    if (cd1 >= DISPLAY_TICKS_LEFT_DEC) {
        cd1 = 0;
        //Voltage
        this->disInstance->setCursor(3, 12);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("VOL:");
        this->printData(data.Voltage, 3, 1);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("V");
        
        //Current
        this->disInstance->setCursor(3, 24);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("CUR:");
        this->printData(data.Current, 3, 1);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("V");
        
        //Power
        this->disInstance->setCursor(3, 36);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("PWR:");
        this->printData(data.Current * data.Voltage, 1, 3);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("W");
        
        //ON-BOARD Voltage
        this->disInstance->setCursor(3, 48);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("OBV:");
        this->printData(powerSupply.obVoltage(), 4);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("V");
        
        //BAT Voltage
        this->disInstance->setCursor(3, 60);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("BAT:");
        this->printData(powerSupply.batVoltage(), 4);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("V");
    }
    
    cd2++;
    if (cd2 >= DISPLAY_TICKS_RIGHT_DEC) {
        cd2 = 0;
        //BTNs
        this->disInstance->setCursor(73, 11);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("L-HVS");
        this->btnStatus(buttons[0]->getPreviousState());
        this->disInstance->setCursor(73, 21);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("L-HVP");
        this->btnStatus(buttons[1]->getPreviousState());
        this->disInstance->setCursor(73, 31);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("L-LVS");
        this->btnStatus(buttons[2]->getPreviousState());
        this->disInstance->setCursor(73, 41);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("L-LVP");
        this->btnStatus(buttons[3]->getPreviousState());
        this->disInstance->setCursor(73, 51);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("R-HVR");
        this->btnStatus(data.HVR);
        this->disInstance->setCursor(73, 61);
        this->disInstance->setFont(u8g2_font_t0_12b_mr);
        this->disInstance->print("R-LVR");
        this->btnStatus(data.LVR);
    }
    
    this->disInstance->home();
    this->disInstance->sendBuffer();
}
