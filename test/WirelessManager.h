//
// Created by lhhlu on 2022/12/3.
//

#ifndef TRANSSIDELOGIC_WIRELESSMANAGER_H
#define TRANSSIDELOGIC_WIRELESSMANAGER_H


#include "Arduino.h"
#include "WString.h"
#include "StatusLED.h"
#include "SoftwareSerial.h"

template <class T>
struct Pack {
    char packType{};    //D, C
    char dataType{};    //I, D, S
    String dataName;
    T data;

    Pack() = default;

    Pack(char packType, char dataType, const String& dataName, T d) {
        this->packType = packType;
        this->dataType = dataType;
        this->dataName = dataName;
        this->data = d;
    }
    
    String str() {
        //Structure: <packType><dataType>|<dataName>|<data>|E
        String content = String(packType) + String(dataType) +"|"
                + dataName + "|" + data + "|" + "E";
        return content;
    }
};


struct RPack : Pack<String> {
    int toInt() const {
        return this->data.toInt();
    }

    double toDouble() const {
        return this->data.toDouble();
    }

    bool toBool() const {
        return (bool)this->data.toInt();
    }

    void load(const String& rawData) {
        this->packType = rawData[0];
        this->dataType = rawData[1];
        String tmpStr = rawData;
        tmpStr.trim();
        tmpStr = tmpStr.substring(3, rawData.length() - 2);
        int tmp = tmpStr.indexOf('|');
        this->dataName = tmpStr.substring(0, tmp);
        this->data = tmpStr.substring(tmp + 1);
    }
};


class WirelessManager {
public:
    WirelessManager(unsigned short tx_pin, unsigned short rx_pin, long ttl_baud = 9600, bool hardware = false,
                    bool inverse = false, bool indicator = true);
    void sendData(const String& dataName, int data);
    void sendData(const String& dataName, double data);
    void sendData(const String& dataName, const String& data);
    RPack readPack();
    int available() const;
    SoftwareSerial *softwareSerial = nullptr;

private:
    void sendStr(const String& str);
    bool hardwareMode = false;
    bool ind = true;
    StatusLED led = StatusLED(12);
};


#endif //TRANSSIDELOGIC_WIRELESSMANAGER_H
