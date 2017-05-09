//
// Created by Elijah on 09/05/2017.
//

#ifndef QUADCOPTER_TESTING_MSPREQUESTS_H
#define QUADCOPTER_TESTING_MSPREQUESTS_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define MSP_ATTITUDE 108

class MSPRequests {
public:
    MSPRequests();

    MSPRequests(uint32_t baudRate, uint8_t softSerialRX, uint8_t softSerialTX);

    void getAttitude(float attitude[]);

private:

    SoftwareSerial *mspSerial;

    void sendMSPRequest(uint8_t cmd, uint8_t *data, uint8_t n_bytes);

};

#endif //QUADCOPTER_TESTING_MSPREQUESTS_H
