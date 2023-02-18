#include "Arduino.h"
#include "../lib/SCoop/SCoop.h"
#include "PowerSupply.h"
#include "Button.h"
#include "StatusLED.h"
#include "WirelessManager.h"
#include "Display.h"

#define BAT_VOLTAGE A5
#define ON_BOARD_5V A4

#define BAT_STAT PIN4

#define RST_D 9
#define CS 10

#define TX_PIN 2
#define RX_PIN 3
#define BAUD 9600

//INPUT
PowerSupply powerSupply(BAT_VOLTAGE, ON_BOARD_5V, BAT_STAT);
Button *LVB_S = new Button(6);
Button *LVB = new Button(5);
Button *HVB_S = new Button(7);
Button *HVB = new Button(8);
Button *buttons[] = {HVB_S, HVB, LVB_S, LVB};
//OUTPUT
StatusLED statusLed_12(12), statusLed_13(13);
//TRANSMISSION
WirelessManager wirelessManager(TX_PIN, RX_PIN, BAUD, false, false, false);
//DISPLAY
Display display(SCK, MOSI, CS, RST_D);
//DATA
RemoteData data;

defineTask(InputReaction)
defineTask(WirelessReaction)

void remoteRelayControl(char rly, bool state) {
    wirelessManager.sendData(String(rly), (int)state);
    statusLed_13.toggle();
}

void InputReaction::setup() {
    //Stay Empty
}

void InputReaction::loop() {
    bool tmp;
    tmp = HVB->readPin();
    if (tmp != HVB->getPreviousState()) {
        HVB->setState(tmp);
        remoteRelayControl('H', tmp);
    }
    tmp = HVB_S->readPin();
    if (tmp != HVB_S->getPreviousState()) {
        HVB_S->setState(tmp);
        remoteRelayControl('H', tmp);
    }
    tmp = LVB->readPin();
    if (tmp != LVB->getPreviousState()) {
        LVB->setState(tmp);
        remoteRelayControl('L', tmp);
    }
    tmp = LVB_S->readPin();
    if (tmp != LVB_S->getPreviousState()) {
        LVB_S->setState(tmp);
        remoteRelayControl('L', tmp);
    }
}

void WirelessReaction::setup() {
    //Stay Empty
}

void WirelessReaction::loop() {
    if (!wirelessManager.available()) return;
    RPack pack = wirelessManager.readPack();
    if (pack.dataName == "V") data.Voltage = pack.toDouble();
    else if (pack.dataName == "C") data.Current = pack.toDouble();
    else if (pack.dataName == "H") data.HVR = pack.toBool();
    else if (pack.dataName == "L") data.LVR = pack.toBool();
    statusLed_12.toggle();
}

void setup() {
    display.setup();
    delay(300);
    display.showStartUpInformation("Initializing IOs");
    powerSupply.setup();
    HVB->setup();
    HVB_S->setup();
    LVB->setup();
    LVB_S->setup();
    statusLed_12.setup();
    statusLed_13.setup();
    delay(300);
    mySCoop.start();
    display.showStartUpInformation("Finished");
    sleep(300);
}

void loop() {
    display.drawMainPage(data, powerSupply, buttons);
    remoteRelayControl('L', true);
    sleep(50);
    yield();
    
}