#include "Arduino.h"
#include "PowerSupply.h"
#include "Button.h"
#include "StatusLED.h"
#include "WirelessManager.h"
#include "Display.h"

//Configurations
#define WirelessBaud 9600
#define SerialBaud 9600

//Hardware configurations
#define RST_D 9             //Display Conf
#define CS 10

#define BAT_VOLTAGE A5      //Battery Conf
#define ON_BOARD_5V A4
#define BAT_STAT PIN4

#define TX_PIN 2            //Wireless Module Conf

//Software configurations
#define RELAY_DATA_CD 100

//INPUT
PowerSupply powerSupply(BAT_VOLTAGE, ON_BOARD_5V, BAT_STAT);       //PS
Button *LVB_S = new Button(6);                                  //BTN
Button *LVB = new Button(5);
Button *HVB_S = new Button(7);
Button *HVB = new Button(8);
Button *buttons[] = {HVB_S, HVB, LVB_S, LVB};
//OUTPUT
StatusLED statusLed_12(12), statusLed_13(13);
//TRANSMISSION
WirelessManager wirelessManager(TX_PIN, MISO, WirelessBaud, false, false, false);
//DISPLAY
Display display(SCK, MOSI, CS, RST_D);
//DATA
RemoteData data;
//UPDATE RATE
long long tick_time = 0;

void remoteRelayControl(char rly, bool state) {
    wirelessManager.sendData(String(rly), state);
    statusLed_13.toggle();
}

bool checkRelayDifference(bool state, Button *btn1, Button *btn2) {
    return state != (btn1->getPreviousState() || btn2->getPreviousState());
}

void setup() {
    Serial.begin(SerialBaud);
    display.setup();
    delay(150);
    display.showStartUpInformation("Initializing IOs");
    powerSupply.setup();
    HVB->setup();
    HVB_S->setup();
    LVB->setup();
    LVB_S->setup();
    statusLed_12.setup();
    statusLed_13.setup();
    wirelessManager.softwareSerial->setTimeout(5);
    delay(150);
    display.showStartUpInformation("Finished");
    delay(150);
}

void loop() {
    //Buttons
    bool tmp;
    tmp = HVB->readPin();
    if (tmp != HVB->getPreviousState()) {
        HVB->setState(tmp);
    }
    tmp = HVB_S->readPin();
    if (tmp != HVB_S->getPreviousState()) {
        HVB_S->setState(tmp);
    }
    tmp = LVB->readPin();
    if (tmp != LVB->getPreviousState()) {
        LVB->setState(tmp);
    }
    tmp = LVB_S->readPin();
    if (tmp != LVB_S->getPreviousState()) {
        LVB_S->setState(tmp);
    }
    
    //Relay data repeater
    tick_time++;
    if (tick_time >= RELAY_DATA_CD) {
        tick_time = 0;
        if (checkRelayDifference(data.LVR, LVB, LVB_S)) {
            remoteRelayControl('L', LVB->getPreviousState() || LVB_S->getPreviousState());
        }
        if (checkRelayDifference(data.HVR, HVB, HVB_S)) {
            remoteRelayControl('H', HVB->getPreviousState() || HVB_S->getPreviousState());
        }
    }
    
    //Display
    display.drawMainPage(data, powerSupply, buttons);
    
    //SerialData handler
    if (wirelessManager.available() <= 0) return;
    RPack pack = wirelessManager.readPack();
    if (pack.dataName == "V") data.Voltage = pack.toDouble();
    else if (pack.dataName == "C") data.Current = pack.toDouble();
    else if (pack.dataName == "H") data.HVR = pack.toBool();
    else if (pack.dataName == "L") data.LVR = pack.toBool();
}