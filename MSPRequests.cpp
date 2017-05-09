//
// Created by Elijah on 09/05/2017.
//

#include "MSPRequests.h"

/**
 * Allows declaration without initialization.
 */
MSPRequests::MSPRequests() {}

/**
 * Initializes MSPRequests object.
 * @param baudRate Baud rate at which to run the SoftwareSerial connection.
 * @param softSerialRX SoftwareSerial RX.
 * @param softSerialTX SoftwareSerial TX.
 */
MSPRequests::MSPRequests(uint32_t baudRate, uint8_t softSerialRX, uint8_t softSerialTX) {
    mspSerial = new SoftwareSerial(softSerialRX, softSerialTX);
    mspSerial->begin(baudRate);
}


/**
 * Sends a MultiWii Serial Protocol Request.
 *
 * @param cmd Request code.
 * @param data Request data.
 * @param n_bytes Number of bytes in data.
 */
void MSPRequests::sendMSPRequest(uint8_t cmd, uint8_t *data, uint8_t n_bytes) {

    uint8_t checksum = 0;

    mspSerial->write((byte *) "$M<", 3);
    mspSerial->write(n_bytes);
    checksum ^= n_bytes;

    mspSerial->write(cmd);
    checksum ^= cmd;

    mspSerial->write(checksum);
}


/**
 * Sends an MSP request for attitude, receives the results and parses them.
 *
 * @param attitude Array of length 3 to contain {roll, pitch, yaw}.
 */
void MSPRequests::getAttitude(float *attitude) {

    // Send MSP Request:
    uint8_t data = 0;
    sendMSPRequest(MSP_ATTITUDE, &data, 0);

    while (!mspSerial->available());

    byte count = 0;

    int16_t roll;
    int16_t pitch;
    int16_t yaw;

    while (mspSerial->available()) {
        count += 1;
        byte c = mspSerial->read();
        switch (count) {
            case 6:
                roll = c;
                break;
            case 7:
                roll <<= 8;
                roll += c;
                roll = (roll & 0xFF00) >> 8 | (roll & 0x00FF) << 8; // Reverse the order of bytes
                break;
            case 8:
                pitch += c;
                break;
            case 9:
                pitch <<= 8;
                pitch += c;
                pitch = (pitch & 0xFF00) >> 8 | (pitch & 0x00FF) << 8; // Reverse the order of bytes
                break;
            case 10:
                yaw += c;
                break;
            case 11:
                yaw <<= 8;
                yaw += c;
                yaw = (yaw & 0xFF00) >> 8 | (yaw & 0x00FF) << 8; // Reverse the order of bytes
                break;
        }
    }

    attitude[0] = roll/10.0;
    attitude[1] = pitch/10.0;
    attitude[2] = yaw;
}