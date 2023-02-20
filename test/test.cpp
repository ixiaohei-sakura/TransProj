//#include <Arduino.h>
//#include "WirelessManager.h"
//
//WirelessManager wirelessManager(3, 2, 9600);
//
//void setup()
//{
//    Serial.begin(9600);
//}
//
//String read(SoftwareSerial *a) {
//    String buffer;
//    buffer = a->readString();
//    buffer.trim();
//    return buffer;
//}
//
//void loop()
//{
////    Serial.print("data = ");
////    Serial.println(read(wirelessManager.softwareSerial));
//
//
////    Serial.print("SF_Available = ");
////    Serial.println(wirelessManager.available());
////    Serial.print("HD_Available = ");
////    Serial.println(Serial.available());
//
//    wirelessManager.sendData("WTF", "SHIT");
//
//    delay(500);
//}


#include <Arduino.h>
#include "WirelessManager.h"

//WirelessManager wirelessManager(3,2, 9600);
SoftwareSerial softwareSerial = SoftwareSerial(MISO, 2);

void setup() {
    Serial.begin(9600);
    softwareSerial.begin(9600);
}

String read(SoftwareSerial a) {
    String buffer;
    buffer = a.readString();
    buffer.trim();
    return buffer;
}

//String read() {
//    String buffer;
//    buffer = Serial1.readString();
//    buffer.trim();
//    return buffer;
//}

void loop() {
    
    
    
//    RPack pack = wirelessManager.readPack();
//    Serial.print("dataName = ");
//    Serial.print(pack.dataName + "   ");
//    Serial.print("dataType = ");
//    Serial.print(String(pack.dataType) + "   ");
//    Serial.print("data = ");
//    Serial.println("   " + pack.data);


    Serial.println(softwareSerial.available());
    Serial.println(softwareSerial.readString());
    

//double a = 0.00;
//a = random() / (double)RANDOM_MAX;
//wirelessManager.sendData("V", "wtf");
//Serial.println(a);
    
    delay(500);
}