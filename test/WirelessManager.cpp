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
        this->softwareSerial->setTimeout(5);
    } else {
        Serial.begin(ttl_baud);
        Serial.setTimeout(5);
    }
}

void WirelessManager::sendData(const String &dataName, int data) {
    this->sendStr(Pack<int>('D', 'I', dataName, data).str());
}

void WirelessManager::sendData(const String &dataName, double data) {
    this->sendStr(Pack<String>('D', 'D', dataName, String(data, 16)).str());
}

void WirelessManager::sendData(const String &dataName, const String& data) {
    this->sendStr(Pack<String>('D', 'S', dataName, data).str());
}

RPack WirelessManager::readPack() {
    String buff;
    RPack pack;
    if (!this->hardwareMode && this->softwareSerial != nullptr) {
        buff = this->softwareSerial->readStringUntil('E') + 'E';
        buff.trim();
        pack.load(buff);
    } else if (this->hardwareMode) {
        buff = Serial.readStringUntil('E') + 'E';
        buff.trim();
        pack.load(buff);
    }
    if (this->ind) {
        this->led.toggle();
    }
    return pack;
}

void WirelessManager::sendStr(const String& str) {
    if (!this->hardwareMode && this->softwareSerial != nullptr) {
        this->softwareSerial->println(str);
    } else if (this->hardwareMode){
        Serial.println(str);
    }
    if (this->ind) {
        this->led.toggle();
    }
}

int WirelessManager::available() const {
    if (!this->hardwareMode && this->softwareSerial != nullptr) {
        return this->softwareSerial->available();
    } else if (this->hardwareMode) {
        return Serial.available();
    } else {
        return 0;
    }
}
