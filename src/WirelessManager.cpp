//
// Created by lhhlu on 2/2/2023.
//

#include "WirelessManager.h"

WirelessManager::WirelessManager(unsigned short tx_pin, unsigned short rx_pin, long ttl_baud, bool hardware,
                                 bool inverse, bool indicator) {
    this->hardwareMode = hardware;
    this->ind = indicator;
    if (!hardware) {
        this->softwareSerial = new SoftwareSerial(rx_pin, tx_pin, inverse);
        this->softwareSerial->begin(ttl_baud);
    } else {
        Serial.begin(ttl_baud);
    }
}

void WirelessManager::sendData(const String &dataName, int data) {
    this->sendStr(Pack<int>('D', 'I', dataName, data).str());
}

void WirelessManager::sendData(const String &dataName, double data) {
    this->sendStr(Pack<double>('D', 'D', dataName, data).str());
}

void WirelessManager::sendData(const String &dataName, const String& data) {
    this->sendStr(Pack<String>('D', 'S', dataName, data).str());
}

RPack WirelessManager::readPack() {
    String buff;
    RPack pack;
    if (!this->hardwareMode && this->softwareSerial != nullptr) {
        buff = this->softwareSerial->readStringUntil('E') + 'E';
        pack.load(buff);
    } else if (this->hardwareMode) {
        buff = Serial.readStringUntil('E') + 'E';
        pack.load(buff);
    }
    if (this->ind) {
        this->led.toggle();
    }
    return pack;
}

void WirelessManager::sendStr(const String& str) {
    if (!this->hardwareMode && this->softwareSerial != nullptr) {
        this->softwareSerial->write(str.c_str());
        this->softwareSerial->flush();
    } else if (this->hardwareMode){
        Serial.write(str.c_str());
        Serial.flush();
    }
    if (this->ind) {
        this->led.toggle();
    }
}

int WirelessManager::available() {
    if (!this->hardwareMode && this->softwareSerial != nullptr) {
        return this->softwareSerial->available();
    } else if (this->hardwareMode) {
        return Serial.available();
    } else {
        return 0;
    }
}
