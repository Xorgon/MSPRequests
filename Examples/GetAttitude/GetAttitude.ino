#include <Arduino.h>
#include <MSPRequests.h>

MSPRequests msp;
float attitude[3];

void setup() {
    msp = MSPRequests(115200, 6, 7);
    Serial.begin(9600);
}

void loop() {
    msp.getAttitude(attitude);
    Serial.println(
            "Roll= " + String(attitude[0]) + ", Pitch= " + String(attitude[1]) + ", Yaw= " + String(attitude[2]));
}