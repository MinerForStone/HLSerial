#include "SerialIO.h"
#include "Arduino.h"

unsigned char* arr;
unsigned char packetSize;

void setupDataBuffer(unsigned char size) {
    packetSize = size;
    arr = realloc(arr, size);
}

void send() {
    unsigned char buf[HEADER_SIZE + packetSize];

    // Header
    buf[0] = 0xFA;
    buf[1] = 0x80;
    buf[2] = packetSize;
    buf[3] = 0x00;

    for (unsigned char i = 0; i < packetSize; i++) {
        buf[i + HEADER_SIZE] = arr[i];
    }

    Serial.write(buf, HEADER_SIZE + packetSize);
}

void writeLong(unsigned char pos, long value) {
    for (unsigned char i = 0; i < 4; i++) {
        arr[i + pos * 4] = value >> 8 * i;
    }
}

void writeByte(unsigned char pos, char value) {
    arr[pos] = value;
}
