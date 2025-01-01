#include "SerialUSB.h"
#include "Arduino.h"
#include "HID-Project.h"

#define dataSize header[2]

unsigned char header[HEADER_SIZE];
unsigned char bufferSize = 0;
unsigned char* data;

void pull() {
    for (unsigned char i = 0; i < 4; i++) { // Reset header cache
        header[i] = 0x00;
    }

    while (Serial1.available() < HEADER_SIZE); // Wait for a full header queue

    while (header[0] != 0xFA || header[1] != 0x80) {
        if (!Serial1.available()) {
            Serial.println("Error: failed to read packet");
            return;
        }

        for (unsigned char i = 0; i < HEADER_SIZE - 1; i++) {
            header[i] = header[i + 1];
        }
        header[HEADER_SIZE - 1] = Serial1.read();
    }

    if (dataSize > bufferSize) {
        data = realloc(data, dataSize);
        bufferSize = dataSize;
    }

    while (Serial1.available() < dataSize); // Wait for all data to be queued

    for (unsigned char i = 0; i < dataSize; i++) {
        data[i] = Serial1.read();
    }
}

long readLong(unsigned char pos) {
    long result = 0;

    for (unsigned char i = 0; i < 4; i++) {
        result += data[i + pos * 4] << 8 * i;
    }

    return result;
}

char readByte(unsigned char pos) {
    return data[pos];
}
